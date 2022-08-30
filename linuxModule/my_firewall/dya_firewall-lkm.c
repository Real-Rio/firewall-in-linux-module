/*
 * @Author: Rio
 * @Date: 2022-08-30 18:46:19
 * @LastEditTime: 2022-08-30 20:01:14
 * @FilePath: /firewall-in-linux-module/linuxModule/my_firewall/dya_firewall-lkm.c
 * @Description:内核模块
 */
#include "netfltr.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("dya");

/* struct to store the rules*/
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
int ruleCount = 0;
struct t_rule T_RULES[100];
static struct nf_hook_ops in_nfho, out_nfho;
static struct net init_net1;

static int myfw_init(void)
{
    printk("my firewall module loaded.\n");

    in_nfho.hook = in_filtrFunc;
    in_nfho.pf = PF_INET;
    in_nfho.hooknum = NF_INET_LOCAL_IN;
    in_nfho.priority = NF_IP_PRI_FIRST; // new version, maybe changed to NF_INET_PRI_FIRST

    out_nfho.hook = out_filtrFunc;
    out_nfho.pf = PF_INET;
    out_nfho.hooknum = NF_INET_LOCAL_OUT;
    out_nfho.priority = NF_IP_PRI_FIRST;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 13, 0)
    nf_register_net_hook(&init_net1, &in_nfho);
    nf_register_net_hook(&init_net1, &out_nfho);
#else
    nf_register_hook(&in_nfho);
    nf_register_hook(&out_nfho);
#endif
    return 0;
}

static void myfw_exit(void)
{
    printk("my firewall module exit ...\n");
    // unregister hook depends on kernel version
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 13, 0)
    nf_register_net_hook(&init_net1, &in_nfho);
    nf_register_net_hook(&init_net1, &out_nfho);
#else
    nf_register_hook(&in_nfho);
    nf_register_hook(&out_nfho);
#endif
}

module_init(myfw_init);
module_exit(myfw_exit);
