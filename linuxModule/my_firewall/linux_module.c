/*
 * @Author: Rio
 * @Date: 2022-08-31 18:22:44
 * @LastEditTime: 2022-09-10 21:44:25
 * @FilePath: /firewall-in-linux-module/linuxModule/my_firewall/linux_module.c
 * @Description:内核模块
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include "netfltr.h"

#define NETLINK_TEST 17

struct sock *nlsk = NULL;
/* struct to store the rules*/
struct t_rule
{
	char pkt;			// 0 - outgoing, 1- incoming, 2 - error
	char block;			// 0 - unblock, 1 - block, 2 - error
	unsigned int srcip; // source ip address
	unsigned int dstip; // destination ip address
	unsigned int srcpt; // source port number
	unsigned int dstpt; // destination port number
	char proto;			// 0 - all, 1 - tcp, 2 - udp, 3 - error
};
int ruleCount = 0;
struct t_rule T_RULES[100];
static struct nf_hook_ops in_nfho, out_nfho;
extern struct netlink_kernel_cfg nltest_cfg;

int __init nltest_init(void)
{
	printk("my firewall module loaded.\n");

	nlsk = netlink_kernel_create(&init_net, NETLINK_TEST, &nltest_cfg);
	if (!nlsk)
	{
		printk("can not create a netlink socket\n");
		return -1;
	}
	printk("netlink_kernel_create() success, nlsk = %p\n", nlsk);

	// mound hook function
	in_nfho.hook = in_filtrFunc;
	in_nfho.pf = PF_INET;
	in_nfho.hooknum = NF_INET_LOCAL_IN;
	in_nfho.priority = NF_IP_PRI_FIRST; // new version, maybe changed to NF_INET_PRI_FIRST

	out_nfho.hook = out_filtrFunc;
	out_nfho.pf = PF_INET;
	out_nfho.hooknum = NF_INET_LOCAL_OUT;
	out_nfho.priority = NF_IP_PRI_FIRST;

// call register function depends on the kernel version
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 13, 0)
	nf_register_net_hook(&init_net, &in_nfho);
	nf_register_net_hook(&init_net, &out_nfho);
#else
	nf_register_hook(&in_nfho);
	nf_register_hook(&out_nfho);
#endif

	return 0;
}

void __exit nltest_exit(void)
{
	sock_release(nlsk->sk_socket);
	printk("Netlink test module exit!\n");

// unregister hook depends on kernel version
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 13, 0)
	nf_unregister_net_hook(&init_net, &in_nfho);
	nf_unregister_net_hook(&init_net, &out_nfho);
#else
	nf_unregister_hook(&in_nfho);
	nf_unregister_hook(&out_nfho);
#endif
}

module_init(nltest_init);
module_exit(nltest_exit);
MODULE_LICENSE("GPL");
