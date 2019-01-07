PROG=proj

SRCS = proj.c keyboard.c timer.c mouse.c video_gr.c vbe.c rtc.c minixforce.c xpm.c entities.c game.c states.c interrupts.c graphics.c movement.c utils.c collision.c

CPPFLAGS += -pedantic #-D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
