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
	{ 0x78f44845, "cdev_del" },
	{ 0x35216b26, "kmalloc_caches" },
	{ 0xa3036ef8, "cdev_init" },
	{ 0x2b68bd2f, "del_timer" },
	{ 0x56470118, "__warn_printk" },
	{ 0xbabacef1, "device_destroy" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x15ba50a6, "jiffies" },
	{ 0xb44ad4b3, "_copy_to_user" },
	{ 0xc5850110, "printk" },
	{ 0xff9c16ee, "device_create" },
	{ 0x24d273d1, "add_timer" },
	{ 0xd2c6f324, "init_net" },
	{ 0x40481db1, "nf_register_net_hook" },
	{ 0x12690e19, "nf_unregister_net_hook" },
	{ 0x7afe113a, "cdev_add" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0xf5cb25c8, "kmem_cache_alloc_trace" },
	{ 0x37a0cba, "kfree" },
	{ 0x69acdf38, "memcpy" },
	{ 0xb356c301, "class_destroy" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x8d62ea07, "__class_create" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "4C70D22A5A852E5F0A44379");
