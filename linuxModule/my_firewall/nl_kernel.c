/*
 * @Author: Rio
 * @Date: 2022-08-30 20:19:24
 * @LastEditTime: 2022-08-31 22:30:32
 * @FilePath: /firewall-in-linux-module/linuxModule/my_firewall/nl_kernel.c
 * @Description:内核中的netlink模块
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include "netfltr.h"
#define NETLINK_TEST 17

struct t_rule
{
    char pkt;           // 0 - outgoing, 1- incoming, 2 - error
    char block;         // 0 - unblock, 1 - block, 2 - error
    unsigned int srcip; // source ip address
    unsigned int dstip; // destination ip address
    unsigned int srcpt; // source port number
    unsigned int dstpt; // destination port number
    char proto;         // 0 - all, 1 - tcp, 2 - udp, 3 - error
};

struct info_to_kernel
{
    char sign;     // 0: add, 1: delete, 2: getRules ,3:test
    char test[20]; //用来测试用的字符串
    struct t_rule rule;
};

extern struct sock *nlsk;
extern int ruleCount;
extern struct t_rule T_RULES[100];

//返回所有规则
void getRules(char *data)
{
    char srcIP[20], dstIP[20], srcPort[20], dstPort[20], action[10], protocol[10], way[5];
    if (!ruleCount)
    {
        sprintf(data, "No rules");
        return;
    }
    int i;
    for (i = 0; i < ruleCount; i++)
    {
        ip_to_str(T_RULES[i].srcip, srcIP);
        ip_to_str(T_RULES[i].dstip, dstIP);
        port_to_str(T_RULES[i].srcpt, srcPort);
        port_to_str(T_RULES[i].dstpt, dstPort);
        if (T_RULES[i].block == '0')
            sprintf(action, "ACCEPT");
        else if (T_RULES[i].block == '1')
            sprintf(action, "DROP");
        if (T_RULES[i].proto == '0')
            sprintf(protocol, "all");
        else if (T_RULES[i].proto == '1')
            sprintf(protocol, "tcp");
        else if (T_RULES[i].proto == '2')
            sprintf(protocol, "udp");
        if (T_RULES[i].pkt == '0')
            sprintf(way, "out");
        else if (T_RULES[i].pkt == '1')
            sprintf(way, "in");

        printk("[RULES]srcIP:%s dstIP:%s srcPORT:%s dstPORT:%s %s %s %s ", srcIP, dstIP, srcPort, dstPort, protocol, way, action);
    }
    sprintf(data, "%s", "test");
}

//添加规则
int addRule(struct info_to_kernel *data)
{
    //前端传一个结构体
    if (ruleCount > 100)
    {
        printk("规则已满\n");
        return 0;
    }
    T_RULES[ruleCount].pkt = data->rule.pkt;
    T_RULES[ruleCount].block = data->rule.block;
    T_RULES[ruleCount].srcip = data->rule.srcip;
    T_RULES[ruleCount].dstip = data->rule.dstip;
    T_RULES[ruleCount].srcpt = data->rule.srcpt;
    T_RULES[ruleCount].dstpt = data->rule.dstpt;
    T_RULES[ruleCount].proto = data->rule.proto;
    ruleCount++;
    printk("[kernel space]current ruleCount is %d\n", ruleCount);
    return 1;
}

int nltest_ksend(char *info, int pid)
{
    char reply[256];
    int rlen;
    struct sk_buff *skb;
    struct nlmsghdr *nlh;
    int retval;

    sprintf(reply, "NLTEST Reply for '%s'", info);
    rlen = strlen(reply) + 1;

    skb = nlmsg_new(rlen, GFP_ATOMIC);
    if (skb == NULL)
    {
        printk("alloc reply nlmsg skb failed!\n");
        return -1;
    }

    nlh = nlmsg_put(skb, 0, 0, 0, NLMSG_SPACE(rlen) - NLMSG_HDRLEN, 0);
    memcpy(NLMSG_DATA(nlh), reply, rlen);
    printk("[kernel space] nlmsglen = %d\n", nlh->nlmsg_len);

    // NETLINK_CB(skb).pid = 0;
    NETLINK_CB(skb).dst_group = 0;

    printk("[kernel space] skb->data send to user: '%s'\n", (char *)NLMSG_DATA(nlh));

    retval = netlink_unicast(nlsk, skb, pid, MSG_DONTWAIT);
    printk("[kernel space] netlink_unicast return: %d\n", retval);
    return 0;
}

void nltest_krecv(struct sk_buff *skb)
{
    printk("[kernel space] nltest_krecv()\n");
    struct nlmsghdr *nlh = NULL;
    struct info_to_kernel *data;
    char returnData[256];
    int pid;

    memset(returnData, 0, 256);

    nlh = nlmsg_hdr(skb);
    if ((nlh->nlmsg_len < NLMSG_HDRLEN) || (skb->len < nlh->nlmsg_len))
    {
        printk("Illegal netlink packet!\n");
        return;
    }

    data = (struct info_to_kernel *)NLMSG_DATA(nlh);
    // printk("[kernel space] data receive from user: '%s'\n", data);
    //对接收data进行判断
    switch (data->sign)
    {
    case '0':
        printk("[kernel space] add rule\n");
        if (addRule(data))
            sprintf(returnData, "%s", "add rule success");
        else
            sprintf(returnData, "%s", "add rule failed");
        break;
    case '1':
    case '2':
        printk("[kernel space] show rule\n");
        getRules(returnData);
        break;

    default:
        break;
    }

    pid = nlh->nlmsg_pid;
    printk("[kernel space] user_pid = %d\n", pid);
    nltest_ksend(returnData, pid);
}

struct netlink_kernel_cfg nltest_cfg = {
    0,            // groups
    0,            // flags
    nltest_krecv, // input
    NULL,         // cb_mutex
    NULL,         // bind
    NULL,         // unbind
    NULL,         // compare
};
