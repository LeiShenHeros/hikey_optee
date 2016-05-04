#include <io.h>
#include <compiler.h>
#include <stdio.h>
#include <trace.h>
#include <kernel/static_ta.h>
#include <mm/tee_pager.h>
#include <mm/tee_mm.h>
#include <string.h>
#include <string_ext.h>
#include <malloc.h>

#define TA_NAME		"sta_reg.ta"

#define SOC_TZPC_BASE_ADDR 0xF8002000

/* 寄存器说明：安全设置状态寄存器
   位域定义UNION结构:  SOC_TZPC_TZPCDECPROT0STAT_UNION */
#define SOC_TZPC_TZPCDECPROT0STAT_ADDR 0x0800

/* 寄存器说明：非安全设置寄存器
   位域定义UNION结构:  SOC_TZPC_TZPCDECPROT0SET_UNION */
#define SOC_TZPC_TZPCDECPROT0SET_ADDR  0x0804

/* 寄存器说明：安全设置寄存器
   位域定义UNION结构:  SOC_TZPC_TZPCDECPROT0CLR_UNION */
#define SOC_TZPC_TZPCDECPROT0CLR_ADDR  0x0808

/* 寄存器说明：安全设置状态寄存器
   位域定义UNION结构:  SOC_TZPC_TZPCDECPROT1STAT_UNION */
#define SOC_TZPC_TZPCDECPROT1STAT_ADDR 0x080C

/* 寄存器说明：非安全设置寄存器
   位域定义UNION结构:  SOC_TZPC_TZPCDECPROT1SET_UNION */
#define SOC_TZPC_TZPCDECPROT1SET_ADDR(base)           ((base) + (0x0810))

/* 寄存器说明：安全设置寄存器
   位域定义UNION结构:  SOC_TZPC_TZPCDECPROT1CLR_UNION */
#define SOC_TZPC_TZPCDECPROT1CLR_ADDR(base)           ((base) + (0x0814))

/* 寄存器说明：安全设置状态寄存器
   位域定义UNION结构:  SOC_TZPC_TZPCDECPROT2STAT_UNION */
#define SOC_TZPC_TZPCDECPROT2STAT_ADDR  0x0818

/* 寄存器说明：非安全设置寄存器
   位域定义UNION结构:  SOC_TZPC_TZPCDECPROT2SET_UNION */
#define SOC_TZPC_TZPCDECPROT2SET_ADDR(base)           ((base) + (0x081C))

/* 寄存器说明：安全设置寄存器
   位域定义UNION结构:  SOC_TZPC_TZPCDECPROT2CLR_UNION */
#define SOC_TZPC_TZPCDECPROT2CLR_ADDR(base)           ((base) + (0x0820))

/* 寄存器说明：安全设置状态寄存器
   位域定义UNION结构:  SOC_TZPC_TZPCDECPROT3STAT_UNION */
#define SOC_TZPC_TZPCDECPROT3STAT_ADDR  0x0824

/* 寄存器说明：非安全设置寄存器
   位域定义UNION结构:  SOC_TZPC_TZPCDECPROT3SET_UNION */
#define SOC_TZPC_TZPCDECPROT3SET_ADDR  0x0828

/* 寄存器说明：安全设置寄存器
   位域定义UNION结构:  SOC_TZPC_TZPCDECPROT3CLR_UNION */
#define SOC_TZPC_TZPCDECPROT3CLR_ADDR(base)           ((base) + (0x082C))


/* #define CONSOLE_UART_BASE 0xF8015000 */
/* #define UART_IBRD 	0x24 */ /* integer baud register */

#define STA_REG_UUID \
		{ 0xd96a5b40, 0x12c7, 0x21af, \
			{ 0x87, 0x94, 0x10, 0x02, 0xa5, 0xd5, 0xc6, 0x1b } }

#define STA_READ_STATS		0
#define STA_WRITE_STATS		1

static TEE_Result read_regs(uint32_t type __unused, TEE_Param p[4] __unused)
{	
	EMSG("TZPC: 0x%x\n",read32(SOC_TZPC_BASE_ADDR));
	EMSG("TZPC: 0x%x\n",read32(SOC_TZPC_BASE_ADDR+SOC_TZPC_TZPCDECPROT0STAT_ADDR));
	EMSG("TZPC: 0x%x\n",read32(SOC_TZPC_BASE_ADDR+SOC_TZPC_TZPCDECPROT1STAT_ADDR));
	EMSG("TZPC: 0x%x\n",read32(SOC_TZPC_BASE_ADDR+SOC_TZPC_TZPCDECPROT2STAT_ADDR));
	EMSG("TZPC: 0x%x\n",read32(SOC_TZPC_BASE_ADDR+SOC_TZPC_TZPCDECPROT3STAT_ADDR));	
	return TEE_SUCCESS;
}

static TEE_Result write_regs(uint32_t type __unused, TEE_Param p[4] __unused)
{

	return TEE_SUCCESS;
}

/*
 * Trusted Application Entry Points
 */

static TEE_Result create_ta(void)
{
	return TEE_SUCCESS;
}

static void destroy_ta(void)
{
}

static TEE_Result open_session(uint32_t ptype __unused,
			       TEE_Param params[4] __unused,
			       void **ppsess __unused)
{
	return TEE_SUCCESS;
}

static void close_session(void *psess __unused)
{
}

static TEE_Result invoke_command(void *psess __unused,
				 uint32_t cmd, uint32_t ptypes,
				 TEE_Param params[4])
{
	switch (cmd) {
	case STA_READ_STATS:
		return read_regs(ptypes, params);
	case STA_WRITE_STATS:
		return write_regs(ptypes, params);
	default:
		break;
	}
	return TEE_ERROR_BAD_PARAMETERS;
}

static_ta_register(.uuid = STA_REG_UUID, .name = TA_NAME,
		   .create_entry_point = create_ta,
		   .destroy_entry_point = destroy_ta,
		   .open_session_entry_point = open_session,
		   .close_session_entry_point = close_session,
		   .invoke_command_entry_point = invoke_command);
