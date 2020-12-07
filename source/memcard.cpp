#include "memcard.h"

int memcard_create() {
#ifdef PS2
  void *ptr = 0;
  int size = 0;
  int fd, fd1;

  mkdir("mc0:BARULAND", 0777);

  fd = open("mc0:BARULAND/icon.sys", O_RDONLY, 0666);
  if (fd < 0) {
    dbglogger_printf("MEMCARD->sys not found\n");
    fd1 = open("mc0:BARULAND/icon.sys", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd1 >= 0) {
      romdisk_find("icon.sys", &ptr, &size);
      dbglogger_printf("MEMCARD->icon.sys (%x\t%d)\n", ptr, size);
      write(fd1, ptr, size);
      close(fd1);
      dbglogger_printf("MEMCARD->sys created\n");
    } else {
      dbglogger_printf("MEMCARD->sys not created\n");
    }
  } else {
    dbglogger_printf("MEMCARD->sys ok\n");
    close(fd);
  }

  fd = open("mc0:BARULAND/baruland.icn", O_RDONLY, 0666);
  if (fd < 0) {
    dbglogger_printf("MEMCARD->ico not found\n");
    fd1 = open("mc0:BARULAND/baruland.icn", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd1 >= 0) {
      romdisk_find("baruland.icn", &ptr, &size);
      dbglogger_printf("MEMCARD->baruland.icn (%x\t%d)\n", ptr, size);
      write(fd1, ptr, size);
      close(fd1);
      dbglogger_printf("MEMCARD->ico created\n");
    } else {
      dbglogger_printf("MEMCARD->ico not created\n");
    }
  } else {
    dbglogger_printf("MEMCARD->ico ok\n");
    close(fd);
  }

  return 0;
#endif
}

void memcard_init() {
#ifdef PS2
  if ((SifLoadModule("rom0:XSIO2MAN", 0, NULL) < 0) ||
      (SifLoadModule("rom0:XMCMAN", 0, NULL) < 0) ||
      (SifLoadModule("rom0:XMCSERV", 0, NULL) < 0)) {
    dbglogger_printf("MEMCARD->Failed to load module memcard modules");
  }

#ifdef TYPE_MC
  if (mcInit(MC_TYPE_MC) < 0) {
#else
  if (mcInit(MC_TYPE_XMC) < 0) {
#endif
    dbglogger_printf("MEMCARD->Failed to initialise memcard server!\n");
  }

  DIR *dir = opendir("mc0:BARULAND");
  if (dir == NULL) {
    dbglogger_printf("MEMCARD->No previous save exists, creating...\n");
    if (memcard_create()) {
      dbglogger_printf("MEMCARD->Failed to create save!");
    }
  } else {
    dbglogger_printf("MEMCARD->Previous save exists\n");
    closedir(dir);
  }
#endif
}