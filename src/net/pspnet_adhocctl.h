/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspnet_adhocctl.h - PSP Adhoc control networking libraries.
 *
 * Copyright (c) 2006 James F.
 * Copyright (c) 2008 InsertWittyName <tias_dp@hotmail.com>
 *
 * Based on the adhoc code in SMS Plus
 * 
 * $Id: pspnet_adhocctl.h 2372 2008-03-23 20:50:32Z iwn $
 */
#ifndef __PSPNETCTL_ADHOC_H__
#define __PSPNETCTL_ADHOC_H__

#ifdef __cplusplus
extern "C" {
#endif

/** Product structure */
struct productStruct
{
	/** Unknown, set to 0 */
	int unknown;
	/** The product ID string */
	char product[9];
} productStruct;

/** Peer info structure */
struct SceNetAdhocctlPeerInfo
{
	struct SceNetAdhocctlPeerInfo *next;
	/** Nickname */
	char nickname[128];	
	/** Mac address */
	unsigned char mac[6];
	/** Unknown */
	unsigned char unknown[6];
	/** Time stamp */
	unsigned long timestamp;
};

/** Scan info structure */
struct SceNetAdhocctlScanInfo
{
	struct SceNetAdhocctlScanInfo *next;
	/** Channel number */
	int channel;
	/** Name (alphanumeric chanracters only) */
	char name[8];
	/** The BSSID */
	unsigned char bssid[6];
	/** Unknown */
	unsigned char unknown[2];
	/** Unknown */
	int unknown2;
};

/**
 * Initialise the Adhoc control library
 *
 * @param unk1 - Set to 0x2000
 * @param unk2 - Set to 0x30
 * @param product - Pass a filled in ::productStruct
 *
 * @return 0 on success, < 0 on error
 */
int sceNetAdhocctlInit(int unk1, int unk2, struct productStruct *product);

/**
 * Terminate the Adhoc control library
 *
 * @return 0 on success, < on error.
 */
int sceNetAdhocctlTerm(void);

/**
 * Connect to the Adhoc control
 *
 * @param unk1 - Pass ""
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlConnect(char *unk1);

/**
 * Disconnect from the Adhoc control
 *
 * @return 0 on success, < 0 on error
 */
int sceNetAdhocctlDisconnect(void);

/**
 * Get the state of the Adhoc control
 *
 * @param event - Pointer to an integer to receive the status. Can continue when it becomes 1.
 *
 * @return 0 on success, < 0 on error
 */
int sceNetAdhocctlGetState(int *event);

/**
 * Connect to the Adhoc control (as a host)
 *
 * @param name - The name of the connection (maximum 8 alphanumeric characters).
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlCreate(char *name);

/**
 * Connect to the Adhoc control (as a client)
 *
 * @param scaninfo - A valid ::SceNetAdhocctlScanInfo struct that has been filled by sceNetAchocctlGetScanInfo
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlJoin(struct SceNetAdhocctlScanInfo *scaninfo);

/**
 * Connect to the Adhoc control game mode (as a host)
 *
 * @param name - The name of the connection (maximum 8 alphanumeric characters).
 * @param unknown - Pass 1.
 * @param num - The total number of players (including the host).
 * @param macs - A pointer to a list of the participating mac addresses, host first, then clients.
 * @param timeout - Timeout in microseconds.
 * @param unknown2 - pass 0.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlCreateEnterGameMode(char *name, int unknown, int num, unsigned char *macs, unsigned int timeout, int unknown2);

/**
 * Connect to the Adhoc control game mode (as a client)
 *
 * @param name - The name of the connection (maximum 8 alphanumeric characters).
 * @param host - The mac address of the host.
 * @param timeout - Timeout in microseconds.
 * @param unknown - pass 0.
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlJoinEnterGameMode(char *name, unsigned char *hostmac, unsigned int timeout, int unknown);

/**
 * Get a list of peers
 *
 * @param length - The length of the list.
 * @param host - An allocated area of size length.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlGetPeerList(int *length, void *buf);

/**
 * Get peer information
 *
 * @param mac - The mac address of the peer.
 * @param size - Size of peerinfo.
 * @param peerinfo - Pointer to store the information.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlGetPeerInfo(unsigned char *mac, int size, struct SceNetAdhocctlPeerInfo *peerinfo);

/**
 * Scan the adhoc channels
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlScan(void);

/**
 * Get the results of a scan
 *
 * @param length - The length of the list.
 * @param host - An allocated area of size length.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlGetScanInfo(int *length, void *buf);

typedef void (*sceNetAdhocctlHandler)(int flag, int error, void *unknown);

/**
 * Register an adhoc event handler
 *
 * @param handler - The event handler.
 * @param unknown - Pass NULL.
 *
 * @return Handler id on success, < 0 on error.
 */
int sceNetAdhocctlAddHandler(sceNetAdhocctlHandler handler, void *unknown);

/**
 * Delete an adhoc event handler
 *
 * @param id - The handler id as returned by sceNetAdhocctlAddHandler.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlDelHandler(int id);

/**
 * Get nickname from a mac address
 *
 * @param mac - The mac address.
 * @param nickname - Pointer to a char buffer where the nickname will be stored.
 *
 * @return 0 on success, < 0 on error.
 */
int sceNetAdhocctlGetNameByAddr(unsigned char *mac, char *nickname);

#ifdef __cplusplus
}
#endif

#endif
