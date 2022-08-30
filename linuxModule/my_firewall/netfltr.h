/*
 * @Author: Rio
 * @Date: 2022-08-30 18:48:51
 * @LastEditTime: 2022-08-30 19:54:37
 * @FilePath: /firewall-in-linux-module/linuxModule/my_firewall/netfltr.h
 * @Description:头文件
 */
#ifndef _NETFLTRHOOKS_H_
#define _NETFLTRHOOKS_H_

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/skbuff.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>

#include "dya_utils.h"

unsigned int in_filtrFunc(void *priv,
                          struct sk_buff *skb,
                          const struct nf_hook_state *state);
unsigned int out_filtrFunc(void *priv,
                           struct sk_buff *skb,
                           const struct nf_hook_state *state);

#endif /* _NETFLTRHOOKS_H_ */
