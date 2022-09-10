#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <linux/netlink.h>
#include <sys/types.h>
#include <unistd.h>
#include "nl_client.h"
#define NETLINK_TEST 17
#define MSG_LEN 256

char *default_data = "Netlink Test Default Data";

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

//前后端通信的结构
struct info_to_kernel
{
    char sign;     // 0: add, 1: delete, 2: getRules ,3:test
    char test[20]; //用来测试用的字符串
    struct t_rule rule;
};

struct msg_to_kernel
{
    struct nlmsghdr hdr;
    // char data[MSG_LEN];
    struct info_to_kernel info;
};

struct u_packet_info
{
    struct nlmsghdr hdr;
    char msg[MSG_LEN];
};

void addRule(struct info_to_kernel *data);

int main(int argc, char *argv[])
{
    // char data[256];
    struct info_to_kernel data;
    int dlen;
    struct sockaddr_nl local;
    struct sockaddr_nl kpeer;
    int skfd, ret, kpeerlen = sizeof(struct sockaddr_nl);
    struct nlmsghdr *message;
    struct u_packet_info info;
    char *retval;

    skfd = socket(PF_NETLINK, SOCK_RAW, NETLINK_TEST);
    if (skfd < 0)
    {
        printf("can not create a netlink socket\n");
        perror("ERROR:");
        return -1;
    }

    memset(&local, 0, sizeof(local));
    local.nl_family = AF_NETLINK;
    local.nl_pid = getpid();
    local.nl_groups = 0;
    if (bind(skfd, (struct sockaddr *)&local, sizeof(local)) != 0)
    {
        printf("bind() error\n");
        return -1;
    }
    memset(&kpeer, 0, sizeof(kpeer));
    kpeer.nl_family = AF_NETLINK;
    kpeer.nl_pid = 0;
    kpeer.nl_groups = 0;

    message = (struct nlmsghdr *)malloc(sizeof(struct msg_to_kernel));
    if (message == NULL)
    {
        printf("malloc() error\n");
        return -1;
    }
    memset(message, '\0', sizeof(struct nlmsghdr));

    message->nlmsg_flags = 0;
    message->nlmsg_type = 0;
    message->nlmsg_seq = 0;
    message->nlmsg_pid = local.nl_pid;

    // keep sending data to kernel until user input 'q'
    while (1)
    {
        memset(&data, 0, sizeof(data));
        printf("请选择要进行的操作\n"
               "0.添加规则\t1.删除规则\t2.获取规则\t3.测试\tq.退出\n");
        // getchar();
        scanf("%c", &data.sign);
        getchar();
        if (data.sign == 'q')
        {
            break;
        }
        if (data.sign < '0' || data.sign > '3')
        {
            printf("输入错误，请重新输入\n");
            continue;
        }
        switch (data.sign)
        {
        case '0':
            addRule(&data);
            break;
            ;
        case '1':
        case '2':
            break;

        default:
            continue;
            ;
        }
        // dlen = strlen(data) + 1;
        dlen = sizeof(struct info_to_kernel);
        //修改nlheader len字段
        message->nlmsg_len = NLMSG_SPACE(dlen); //头+data

        retval = memcpy(NLMSG_DATA(message), &data, sizeof(data));

        // printf("message sendto kernel, content: '%s', len: %d\n", (char *)NLMSG_DATA(message), message->nlmsg_len);
        ret = sendto(skfd, message, message->nlmsg_len, 0, (struct sockaddr *)&kpeer, sizeof(kpeer));
        if (!ret)
        {
            perror("sendto:");
            exit(-1);
        }
        // printf("send successfully\n");
        ret = recvfrom(skfd, &info, sizeof(struct u_packet_info), 0, (struct sockaddr *)&kpeer, &kpeerlen);
        if (!ret)
        {
            perror("recvfrom:");
            exit(-1);
        }

        printf("message recvfrom kernel, content: '%s'\n", (char *)info.msg);
    }
    close(skfd);
    return 0;
}

void addRule(struct info_to_kernel *data)
{
    char srcIP[20], dstIP[20], srcPort[20], dstPort[20], action[10], protocol[10], way[5];
    printf("接下来输入要添加的规则的信息(*为任意)\n");
    printf("请输入源ip地址(*.*.*.*):");
    scanf("%s", srcIP);
    data->rule.srcip = str_to_ip(srcIP, strlen(srcIP));
    printf("请输入目的ip地址(*.*.*.*):");
    scanf("%s", dstIP);
    data->rule.dstip = str_to_ip(dstIP, strlen(dstIP));
    printf("请输入源端口号:");
    scanf("%s", srcPort);
    data->rule.srcpt = str_to_port(srcPort);
    printf("请输入目的端口号:");
    scanf("%s", dstPort);
    data->rule.dstpt = str_to_port(dstPort);
    printf("请输入协议(tcp:1/udp:2/all:0):");
    getchar();
    scanf("%c", &data->rule.proto);
    getchar();
    printf("请输入方向(入站:1,出站:0):");
    scanf("%c", &data->rule.pkt);
    getchar();
    printf("请输入规则(允许:0,丢弃:1):");
    scanf("%c", &data->rule.block);
    getchar();
}
