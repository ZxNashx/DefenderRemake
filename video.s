; video_base.s
; Assembly routines for setting and getting the video base register on Atari ST


	xdef _set_video_base_asm

_set_video_base_asm:
	move.w 4(sp),d0
	lea $00FF8201,a0
	movep.w d0,(a0)
	rts
