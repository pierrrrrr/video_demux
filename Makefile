CFLAGS += -lavformat -lavcodec

CC += -std=c99 $(CFLAGS)


video_demux: video_demux.c
	$(CC) $< -o $@

test: video_demux
	./video_demux test.mp4

clean:
	rm -f video_demux

