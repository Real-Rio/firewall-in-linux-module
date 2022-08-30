#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xb3753869, "module_layout" },
	{ 0x4eb666, "sock_release" },
	{ 0xb8e6ca84, "__netlink_kernel_create" },
	{ 0xd2c6f324, "init_net" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x8fb5bd0f, "netlink_unicast" },
	{ 0xc5850110, "printk" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0x81654721, "__nlmsg_put" },
	{ 0x179a6375, "__alloc_skb" },
	{ 0xa916b694, "strnlen" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "7205E5B9CAF6ED6CBB12C87");
