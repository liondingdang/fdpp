/****************************************************************/
/*                                                              */
/*                          proto.h                             */
/*                                                              */
/*                   Global Function Prototypes                 */
/*                                                              */
/*                   Copyright (c) 1995, 1996                   */
/*                      Pasquale J. Villani                     */
/*                      All Rights Reserved                     */
/*                                                              */
/* This file is part of DOS-C.                                  */
/*                                                              */
/* DOS-C is free software; you can redistribute it and/or       */
/* modify it under the terms of the GNU General Public License  */
/* as published by the Free Software Foundation; either version */
/* 2, or (at your option) any later version.                    */
/*                                                              */
/* DOS-C is distributed in the hope that it will be useful, but */
/* WITHOUT ANY WARRANTY; without even the implied warranty of   */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See    */
/* the GNU General Public License for more details.             */
/*                                                              */
/* You should have received a copy of the GNU General Public    */
/* License along with DOS-C; see the file COPYING.  If not,     */
/* write to the Free Software Foundation, 675 Mass Ave,         */
/* Cambridge, MA 02139, USA.                                    */
/****************************************************************/

#ifdef MAIN
#ifdef VERSION_STRINGS
static BYTE *Proto_hRcsId =
    "$Id: proto.h 1491 2009-07-18 20:48:44Z bartoldeman $";
#endif
#endif

/* blockio.c */
__FAR(struct buffer)getblk(ULONG blkno, COUNT dsk, BOOL overwrite);
#define getblock(blkno, dsk) getblk(blkno, dsk, FALSE);
#define getblockOver(blkno, dsk) getblk(blkno, dsk, TRUE);
VOID setinvld(REG COUNT dsk);
BOOL dirty_buffers(REG COUNT dsk);
BOOL flush_buffers(REG COUNT dsk);
BOOL flush(void);
BOOL fill(__FAR(REG struct buffer) bp, ULONG blkno, COUNT dsk);
BOOL DeleteBlockInBufferCache(ULONG blknolow, ULONG blknohigh, COUNT dsk, int mode);
/* *** Changed on 9/4/00  BER */
UWORD dskxfer(COUNT dsk, ULONG blkno,__FAR(VOID) buf, UWORD numblocks,
              COUNT mode);
/* *** End of change */
void AllocateHMASpace (size_t lowbuffer, size_t highbuffer);

/* break.c */
unsigned char ctrl_break_pressed(void);
unsigned char check_handle_break(__DOSFAR(struct dhdr)*pdev);
void handle_break(__DOSFAR(struct dhdr)*pdev, int sft_out);
#ifdef __WATCOMC__
#pragma aux handle_break aborts;
#endif

/* chario.c */
__FAR(struct dhdr)sft_to_dev(__FAR(sft)sft);
long BinaryCharIO(__DOSFAR(struct dhdr)*pdev, size_t n,__FAR(void) bp,
                  unsigned command);
int ndread(__DOSFAR(struct dhdr)*pdev);
int StdinBusy(void);
void con_flush(__DOSFAR(struct dhdr)*pdev);
unsigned char read_char(int sft_in, int sft_out, BOOL check_break);
unsigned char read_char_stdin(BOOL check_break);
long cooked_read(__FAR(struct dhdr)*pdev, size_t n,__FAR(char)bp);
void read_line(int sft_in, int sft_out,__FAR(keyboard) kp);
size_t read_line_handle(int sft_idx, size_t n,__FAR(char) bp);
void write_char(int c, int sft_idx);
void write_char_stdout(int c);
void update_scr_pos(unsigned char c, unsigned char count);
long cooked_write(__DOSFAR(struct dhdr)*pdev, size_t n,__FAR(const char)bp);

__FAR(sft)get_sft(UCOUNT);

/* dosfns.c */
__FAR(const char)get_root(__FAR(const char));
BOOL check_break(void);
UCOUNT GenericReadSft(__FAR(sft) sftp, UCOUNT n,__FAR(void) bp,
                      COUNT * err, BOOL force_binary);
COUNT SftSeek(int sft_idx, LONG new_pos, unsigned mode);
/*COUNT DosRead(COUNT hndl, UCOUNT n,__FAR(BYTE) bp,__FAR(COUNT) err); */
void BinarySftIO(int sft_idx, void *bp, int mode);
#define BinaryIO(hndl, bp, mode) BinarySftIO(get_sft_idx(hndl), bp, mode)
long DosRWSft(int sft_idx, size_t n,__FAR(void) bp, int mode);
#define DosRead(hndl, n, bp) DosRWSft(get_sft_idx(hndl), n, bp, XFR_READ)
#define DosWrite(hndl, n, bp) DosRWSft(get_sft_idx(hndl), n, bp, XFR_WRITE)
ULONG DosSeek(unsigned hndl, LONG new_pos, COUNT mode, int *rc);
long DosOpen(__FAR(char) fname, unsigned flags, unsigned attrib);
COUNT CloneHandle(unsigned hndl);
long DosDup(unsigned Handle);
COUNT DosForceDup(unsigned OldHandle, unsigned NewHandle);
long DosOpenSft(__FAR(char) fname, unsigned flags, unsigned attrib);
COUNT DosClose(COUNT hndl);
COUNT DosCloseSft(int sft_idx, BOOL commitonly);
#define DosCommit(hndl) DosCloseSft(get_sft_idx(hndl), TRUE)
UWORD DosGetFree(UBYTE drive, UWORD * navc, UWORD * bps, UWORD * nc);
COUNT DosGetCuDir(UBYTE drive,__FAR(BYTE) s);
COUNT DosChangeDir(__FAR(BYTE) s);
COUNT DosFindFirst(UCOUNT attr,__FAR(BYTE) name);
COUNT DosFindNext(void);
COUNT DosGetFtime(COUNT hndl, date * dp, _time * tp);
COUNT DosSetFtimeSft(int sft_idx, date dp, _time tp);
#define DosSetFtime(hndl, dp, tp) DosSetFtimeSft(get_sft_idx(hndl), (dp), (tp))
COUNT DosGetFattr(__FAR(BYTE) name);
COUNT DosSetFattr(__FAR(BYTE) name, UWORD attrp);
UBYTE DosSelectDrv(UBYTE drv);
COUNT DosDelete(__FAR(BYTE) path, int attrib);
COUNT DosRename(__FAR(BYTE) path1,__FAR(BYTE) path2);
COUNT DosRenameTrue(BYTE * path1, BYTE * path2, int attrib);
COUNT DosMkRmdir(__FAR(const char) dir, int action);
__FAR(struct dhdr)IsDevice(__FAR(const char) FileName);
BOOL IsShareInstalled(BOOL recheck);
COUNT DosLockUnlock(COUNT hndl, LONG pos, LONG len, COUNT unlock);
int idx_to_sft_(int SftIndex);
__FAR(sft)idx_to_sft(int SftIndex);
int get_sft_idx(UCOUNT hndl);
__FAR(struct cds)get_cds(unsigned dsk);
__FAR(struct cds)get_cds1(unsigned dsk);
COUNT DosTruename(__FAR(const char) src,__FAR(char) dest);

/* dosidle.asm */
VOID ASMFUNC DosIdle_int(void);
VOID ASMFUNC DosIdle_hlt(void);
#ifdef __WATCOMC__
#pragma aux (cdecl) DosIdle_int modify exact []
#pragma aux (cdecl) DosIdle_hlt modify exact []
#endif

/* error.c */
VOID dump(void);
VOID panic(const BYTE * s);
VOID fatal(const BYTE * err_msg);

/* fatdir.c */
VOID dir_init_fnode(f_node_ptr fnp, CLUSTER dirstart);
f_node_ptr dir_open(const char *dirname, BOOL split, f_node_ptr fnp);
COUNT dir_read(REG f_node_ptr fnp);
BOOL dir_write_update(REG f_node_ptr fnp, BOOL update);
#define dir_write(fnp) dir_write_update(fnp, FALSE)
COUNT dos_findfirst(UCOUNT attr, BYTE * name);
COUNT dos_findnext(void);
void ConvertName83ToNameSZ(__FAR(BYTE) destSZ,__FAR(BYTE) srcFCBName);
const char *ConvertNameSZToName83(char *destFCBName, const char *srcSZ);

/* fatfs.c */
__FAR(struct dpb)get_dpb(COUNT dsk);
ULONG clus2phys(CLUSTER cl_no,__FAR(struct dpb) dpbp);
int dos_open(char * path, unsigned flag, unsigned attrib, int fd);
BOOL fcbmatch(const char *fcbname1, const char *fcbname2);
BOOL fcmp_wild(const char * s1, const char * s2, unsigned n);
VOID touc(BYTE * s, COUNT n);
COUNT dos_close(COUNT fd);
COUNT dos_delete(BYTE * path, int attrib);
COUNT dos_rmdir(BYTE * path);
COUNT dos_rename(BYTE * path1, BYTE * path2, int attrib);
date dos_getdate(void);
_time dos_gettime(void);
COUNT dos_mkdir(BYTE * dir);
BOOL last_link(f_node_ptr fnp);
COUNT map_cluster(REG f_node_ptr fnp, COUNT mode);
long rwblock(COUNT fd,__FAR(VOID) buffer, UCOUNT count, int mode);
COUNT dos_read(COUNT fd,__FAR(VOID) buffer, UCOUNT count);
COUNT dos_write(COUNT fd,__FAR(const VOID) buffer, UCOUNT count);
CLUSTER dos_free(__FAR(struct dpb) dpbp);
BOOL dir_exists(char * path);
VOID dpb16to32(__FAR(struct dpb)dpbp);

f_node_ptr split_path(const char *, f_node_ptr fnp);

int dos_cd(char * PathName);

COUNT dos_getfattr(BYTE * name);
COUNT dos_setfattr(BYTE * name, UWORD attrp);
COUNT media_check(__FAR(REG struct dpb) dpbp);
f_node_ptr xlt_fd(COUNT fd);
COUNT xlt_fnp(f_node_ptr fnp);
__FAR(struct dhdr) select_unit(COUNT drive);
void dos_merge_file_changes(int fd);

/* fattab.c */
void read_fsinfo(__FAR(struct dpb) dpbp);
void write_fsinfo(__FAR(struct dpb) dpbp);
CLUSTER link_fat(__FAR(struct dpb) dpbp, CLUSTER Cluster1,
                 REG CLUSTER Cluster2);
CLUSTER next_cluster(__FAR(struct dpb) dpbp, REG CLUSTER ClusterNum);
BOOL is_free_cluster(__FAR(struct dpb) dpbp, REG CLUSTER ClusterNum);

/* fcbfns.c */
VOID DosOutputString(__FAR(BYTE) s);
int DosCharInputEcho(VOID);
int DosCharInput(VOID);
VOID DosDirectConsoleIO(__FAR(iregs) r);
VOID DosCharOutput(COUNT c);
VOID DosDisplayOutput(COUNT c);
__FAR(UBYTE)FatGetDrvData(UBYTE drive, UBYTE * spc, UWORD * bps,
                   UWORD * nc);
UWORD FcbParseFname(UBYTE *wTestMode,__FAR(const BYTE)lpFileName,__FAR(fcb) lpFcb);
__FAR(const BYTE)ParseSkipWh(__FAR(const BYTE) lpFileName);
BOOL TestCmnSeps(__FAR(BYTE) lpFileName);
BOOL TestFieldSeps(__FAR(BYTE) lpFileName);
__FAR(const BYTE)GetNameField(__FAR(const BYTE) lpFileName,__FAR(BYTE) lpDestField,
                       COUNT nFieldSize, BOOL * pbWildCard);
UBYTE FcbReadWrite(__FAR(xfcb), UCOUNT, int);
UBYTE FcbGetFileSize(__FAR(xfcb) lpXfcb);
void FcbSetRandom(__FAR(xfcb) lpXfcb);
UBYTE FcbRandomBlockIO(__FAR(xfcb) lpXfcb, UWORD *nRecords, int mode);
UBYTE FcbRandomIO(__FAR(xfcb) lpXfcb, int mode);
UBYTE FcbOpen(__FAR(xfcb) lpXfcb, unsigned flags);
UBYTE FcbDelete(__FAR(xfcb) lpXfcb);
UBYTE FcbRename(__FAR(xfcb) lpXfcb);
UBYTE FcbClose(__FAR(xfcb) lpXfcb);
void FcbCloseAll(void);
UBYTE FcbFindFirstNext(__FAR(xfcb) lpXfcb, BOOL First);

/* intr.asm */
COUNT ASMPASCAL res_DosExec(COUNT mode, exec_blk * ep, BYTE * lp);
UCOUNT ASMPASCAL res_read(int fd, void *buf, UCOUNT count);
#ifdef __WATCOMC__
#pragma aux (pascal) res_DosExec modify exact [ax bx dx es]
#pragma aux (pascal) res_read modify exact [ax bx cx dx]
#endif

/* ioctl.c */
COUNT DosDevIOctl(lregs * r);

/* memmgr.c */
seg far2para(__FAR(VOID) p);
seg long2para(ULONG size);
__FAR(void)add_far(__FAR(void) fp, unsigned off);
__FAR(VOID)adjust_far(__FAR(const void) fp);
COUNT DosMemAlloc(UWORD size, COUNT mode, seg * para, UWORD * asize);
COUNT DosMemLargest(UWORD * size);
COUNT DosMemFree(UWORD para);
COUNT DosMemChange(UWORD para, UWORD size, UWORD * maxSize);
COUNT DosMemCheck(void);
COUNT FreeProcessMem(UWORD ps);
COUNT DosGetLargestBlock(UWORD * block);
VOID show_chain(void);
void DosUmbLink(unsigned n);
VOID mcb_print(__FAR(mcb) mcbp);

/* lfnapi.c */
COUNT lfn_allocate_inode(VOID);
COUNT lfn_free_inode(COUNT handle);

COUNT lfn_setup_inode(COUNT handle, ULONG dirstart, UWORD diroff);

COUNT lfn_create_entries(COUNT handle, lfn_inode_ptr lip);
COUNT lfn_remove_entries(COUNT handle);

COUNT lfn_dir_read(COUNT handle, lfn_inode_ptr lip);
COUNT lfn_dir_write(COUNT handle);

/* nls.c */
BYTE DosYesNo(UWORD ch);
#ifndef DosUpMem
VOID DosUpMem(__FAR(VOID) str, unsigned len);
#endif
unsigned char ASMCFUNC SEGM(HMA_TEXT) DosUpChar(unsigned char ch);
VOID DosUpString(__FAR(char) str);
VOID DosUpFMem(__FAR(VOID) str, unsigned len);
unsigned char DosUpFChar(unsigned char ch);
VOID DosUpFString(__FAR(char) str);
COUNT DosGetData(int subfct, UWORD cp, UWORD cntry, UWORD bufsize,
                 __FAR(VOID) buf);
#ifndef DosGetCountryInformation
COUNT DosGetCountryInformation(UWORD cntry,__FAR(VOID) buf);
#endif
#ifndef DosSetCountry
COUNT DosSetCountry(UWORD cntry);
#endif
COUNT DosGetCodepage(UWORD * actCP, UWORD * sysCP);
COUNT DosSetCodepage(UWORD actCP, UWORD sysCP);
__FAR(VOID)DosGetDBCS(void);
UWORD ASMCFUNC SEGM(HMA_TEXT) syscall_MUX14(__FAR(iregs) regs);

/* prf.c */
#ifdef DEBUG
int VA_CDECL _printf(CONST char * fmt, ...) PRINTF(1);
int VA_CDECL _sprintf(char * buff, CONST char * fmt, ...) PRINTF(2);
#endif
VOID hexd(const char *title,__FAR(VOID) p, COUNT numBytes);
void put_unsigned(unsigned n, int base, int width);
void put_string(const char *s);
void put_console(int);

#ifndef USE_STDLIB
/* strings.c */
//size_t strlen(const char * s);
size_t fstrlen(__FAR(const char) s);
//__FAR(char) _fstrcpy(__FAR(char) d,__FAR(const char) s);
//int strcmp(const char * d, const char * s);
int fstrcmp(__FAR(const char) d,__FAR(const char) s);
int fstrncmp(__FAR(const char) d,__FAR(const char) s, size_t l);
//int strncmp(const char * d, const char * s, size_t l);
//char * strchr(const char * s, int c);

/* misc.c */
//char * strcpy(char * d, const char * s);
//void ASMPASCAL fmemcpyBack(__FAR(void) d,__FAR(const void) s, size_t n);
void fmemcpy(__FAR(void) d,__FAR(const void) s, size_t n);
void fmemcpy_n(void *d,__FAR(const void) s, size_t n);
void fstrcpy(__FAR(char) d,__FAR(const char) s);
//void * memcpy(void *d, const void * s, size_t n);
void fmemset(__FAR(void) s, int ch, size_t n);
//void * memset(void * s, int ch, size_t n);

//int memcmp(const void *m1, const void *m2, size_t n);
int fmemcmp(__FAR(const void)m1,__FAR(const void)m2, size_t n);

#ifdef __WATCOMC__
/* bx, cx, dx and es not used or clobbered for all asmsupt.asm functions except
   (f)memchr/(f)strchr (which clobber dx) */
#pragma aux (pascal) pascal_ax modify exact [ax]
#pragma aux (pascal_ax) fmemcpy
#pragma aux (pascal_ax) memcpy
#pragma aux (pascal_ax) fmemset
#pragma aux (pascal_ax) memset
#pragma aux (pascal_ax) fmemcmp modify nomemory
#pragma aux (pascal_ax) memcmp modify nomemory
#pragma aux (pascal_ax) fstrcpy
#pragma aux (pascal_ax) strcpy
#pragma aux (pascal_ax) fstrlen modify nomemory
#pragma aux (pascal_ax) strlen modify nomemory
#pragma aux (pascal) memchr modify exact [ax dx] nomemory
#pragma aux (pascal) fmemchr modify exact [ax dx] nomemory
#pragma aux (pascal) strchr modify exact [ax dx] nomemory
#pragma aux (pascal) fstrchr modify exact [ax dx] nomemory
#endif
#else    // USE_STDLIB
#define fstrlen strlen
#define fstrcpy strcpy
#define fstrcmp strcmp
#define fstrncmp strncmp

#define fmemcpy memcpy
#define fmemcpy_n memcpy
#define fmemset memset
#define fmemcmp memcmp
#endif
__FAR(char) fstrchr(__FAR(const char) s, int c);
__FAR(void) fmemchr(__FAR(const void) s, int c, size_t n);

/* sysclk.c */
COUNT BcdToByte(COUNT x);
COUNT BcdToWord(BYTE * x, UWORD * mon, UWORD * day, UWORD * yr);
LONG WordToBcd(BYTE * x, UWORD * mon, UWORD * day, UWORD * yr);

/* syspack.c */
#ifdef NONNATIVE
VOID getdirent(__FAR(UBYTE) vp,__FAR(struct dirent) dp);
VOID putdirent(__FAR(struct dirent) dp,__FAR(UBYTE) vp);
#else
#define getdirent(vp, dp) fmemcpy(dp, vp, sizeof(struct dirent))
#define putdirent(dp, vp) fmemcpy(vp, dp, sizeof(struct dirent))
#endif

/* systime.c */
void DosGetTime(struct dostime *dt);
int DosSetTime(const struct dostime *dt);
unsigned char DosGetDate(struct dosdate *dd);
int DosSetDate(const struct dosdate *dd);

const UWORD *is_leap_year_monthdays(UWORD year);
UWORD DaysFromYearMonthDay(UWORD Year, UWORD Month, UWORD DayOfMonth);

/* task.c */
VOID new_psp(seg para, seg cur_psp);
VOID child_psp(seg para, seg cur_psp, int psize);
VOID return_user(void);
COUNT DosExec(COUNT mode,__FAR(exec_blk) ep,__FAR(BYTE) lp);
ULONG SftGetFsize(int sft_idx);
VOID InitPSP(VOID);

/* newstuff.c */
int SetJFTSize(UWORD nHandles);
long DosMkTmp(__FAR(BYTE) pathname, UWORD attr);
COUNT truename(__FAR(const char) src, char * dest, COUNT t);

/* network.c */
int network_redirector(unsigned cmd);
int network_redirector_fp(unsigned cmd, __FAR(void)s);
long ASMPASCAL network_redirector_mx(unsigned cmd, __FAR(void)s, UDWORD arg);
#define remote_rw(cmd,s,arg) network_redirector_mx(cmd, s, arg)
#define remote_getfree(s,d) (int)network_redirector_mx(REM_GETSPACE, s, GET_FP32(d))
#define remote_lseek(s,new_pos) network_redirector_mx(REM_LSEEK, s, GET_FP32(new_pos))
#define remote_setfattr(attr) (int)network_redirector_mx(REM_SETATTR, NULL, attr)
#define remote_printredir(dx,ax) (int)network_redirector_mx(REM_PRINTREDIR, MK_FP(0,dx), ax)
#define QRemote_Fn(d,s) (int)network_redirector_mx(REM_FILENAME, d, GET_FP32(s))

UWORD get_machine_name(__FAR(BYTE) netname);
VOID set_machine_name(__FAR(BYTE) netname, UWORD name_num);

/* procsupt.asm */
VOID ASMFUNC exec_user(__FAR(iregs) irp, int disable_a20);

/* new by TE */

/*
    assert at compile time, that something is true.

    use like
        ASSERT_CONST( SECSIZE == 512)
        ASSERT_CONST( (__FAR(BYTE))x->fcb_ext - (__FAR(BYTE))x->fcbname == 8)
*/

#define ASSERT_CONST(x) { typedef struct { char _xx[x ? 1 : -1]; } xx ; }

WORD ASMCFUNC SEGM(HMA_TEXT) FAR clk_driver(__DOSFAR(request) rp);
COUNT ASMCFUNC SEGM(HMA_TEXT) FAR blk_driver(__DOSFAR(request) rp);
VOID ASMCFUNC SEGM(INIT_TEXT) FreeDOSmain(void);
VOID ASMCFUNC SEGM(HMA_TEXT) int21_syscall(__FAR(iregs) irp);
VOID ASMCFUNC SEGM(HMA_TEXT) int21_service(__FAR(iregs) r);
struct int25regs;
VOID ASMCFUNC SEGM(HMA_TEXT) int2526_handler(WORD mode,__FAR(struct int25regs) r);
struct config;
VOID ASMCFUNC SEGM(HMA_TEXT) FAR P_0(__FAR(struct config)Config);
struct int2f12regs;
VOID ASMCFUNC SEGM(HMA_TEXT) int2F_12_handler(struct int2f12regs r);

BOOL ASMPASCAL fl_reset(WORD);
COUNT ASMPASCAL fl_diskchanged(WORD);

COUNT ASMPASCAL fl_format(WORD, WORD, WORD, WORD, WORD,__FAR(UBYTE));
COUNT ASMPASCAL fl_read(WORD, WORD, WORD, WORD, WORD,__FAR(UBYTE));
COUNT ASMPASCAL fl_write(WORD, WORD, WORD, WORD, WORD,__FAR(UBYTE));
COUNT ASMPASCAL fl_verify(WORD, WORD, WORD, WORD, WORD,__FAR(UBYTE));
COUNT ASMPASCAL fl_setdisktype(WORD, WORD);
COUNT ASMPASCAL fl_setmediatype(WORD, WORD, WORD);
VOID ASMPASCAL fl_readkey(VOID);
COUNT ASMPASCAL fl_lba_ReadWrite(BYTE drive, WORD mode,__FAR(struct _bios_LBA_address_packet) dap_p);
UWORD ASMPASCAL floppy_change(UWORD);
#ifdef __WATCOMC__
#pragma aux (pascal) fl_reset modify exact [ax dx]
#pragma aux (pascal) fl_diskchanged modify exact [ax dx]
#pragma aux (pascal) fl_setdisktype modify exact [ax bx dx]
#pragma aux (pascal) fl_readkey modify exact [ax]
#pragma aux (pascal) fl_lba_ReadWrite modify exact [ax dx]
#pragma aux (pascal) floppy_change modify exact [ax cx dx]
#endif

        /* DOS calls this to see if it's okay to open the file.
           Returns a file_table entry number to use (>= 0) if okay
           to open.  Otherwise returns < 0 and may generate a critical
           error.  If < 0 is returned, it is the negated error return
           code, so DOS simply negates this value and returns it in
           AX. */
int ASMPASCAL share_open_check(char * filename, unsigned short pspseg, int openmode, int sharemode);     /* SHARE_COMPAT, etc... */

        /* DOS calls this to record the fact that it has successfully
           closed a file, or the fact that the open for this file failed. */
void ASMPASCAL share_close_file(int fileno);       /* file_table entry number */

        /* DOS calls this to determine whether it can access (read or
           write) a specific section of a file.  We call it internally
           from lock_unlock (only when locking) to see if any portion
           of the requested region is already locked.  If pspseg is zero,
           then it matches any pspseg in the lock table.  Otherwise, only
           locks which DO NOT belong to pspseg will be considered.
           Returns zero if okay to access or lock (no portion of the
           region is already locked).  Otherwise returns non-zero and
           generates a critical error (if allowcriter is non-zero).
           If non-zero is returned, it is the negated return value for
           the DOS call. */
int ASMPASCAL share_access_check(unsigned short pspseg, int fileno, unsigned long ofs, unsigned long len, int allowcriter); /* allow a critical error to be generated */

        /* DOS calls this to lock or unlock a specific section of a file.
           Returns zero if successfully locked or unlocked.  Otherwise
           returns non-zero.
           If the return value is non-zero, it is the negated error
           return code for the DOS 0x5c call. */
int ASMPASCAL share_lock_unlock(unsigned short pspseg, int fileno, unsigned long ofs, unsigned long len, int unlock);       /* one to unlock; zero to lock */

unsigned char ASMPASCAL share_check(void);

long ASMPASCAL call_nls(UWORD,__FAR(VOID), UWORD, UWORD, UWORD, UWORD);

ULONG ASMPASCAL ReadPCClock(VOID);
VOID ASMPASCAL WriteATClock(BYTE *, BYTE, BYTE, BYTE);
VOID ASMPASCAL WritePCClock(ULONG);

VOID ASMFUNC FAR cpm_entry(VOID);
COUNT ASMFUNC CriticalError(COUNT nFlag, COUNT nDrive, COUNT nError,__FAR(struct dhdr) lpDevice);
VOID ASMFUNC FAR CharMapSrvc(VOID);

unsigned ASMPASCAL init_call_intr(int nr, iregs * rp);
unsigned ASMPASCAL read(int fd, void *buf, unsigned count);
int ASMPASCAL init_DosOpen(const char *pathname, int flags);
int ASMPASCAL close(int fd);
int ASMPASCAL dup2(int oldfd, int newfd);
ULONG ASMPASCAL lseek(int fd, long position);
seg ASMPASCAL allocmem(UWORD size);
void ASMPASCAL keycheck(void);
void ASMPASCAL set_DTA(__FAR(void)_dta);
WORD ASMPASCAL execrh(__FAR(request),__FAR(struct dhdr));
VOID ASMPASCAL FAR _EnableA20(VOID);
VOID ASMPASCAL FAR _DisableA20(VOID);
__FAR(void) ASMPASCAL DetectXMSDriver(VOID);
int ASMPASCAL init_call_XMScall(__FAR(void) driverAddress, UWORD ax, UWORD dx);

void ASMPASCAL init_PSPSet(seg psp_seg);
int ASMPASCAL init_DosExec(int mode, exec_blk * ep, char * lp);
int ASMPASCAL init_setdrive(int drive);
int ASMPASCAL init_switchar(int chr);
//COUNT ASMPASCAL Umb_Test(void);
COUNT ASMPASCAL UMB_get_largest(__FAR(void) driverAddress, UWORD * __seg, UCOUNT * size);
VOID ASMFUNC init_stacks(__FAR(VOID) stack_base, COUNT nStacks, WORD stackSize);
void ASMFUNC spawn_int23(void);        /* procsupt.asm */
/* kernel.asm */
VOID ASMFUNC FAR init_call_p_0(__FAR(struct config)Config); /* P_0, actually */
