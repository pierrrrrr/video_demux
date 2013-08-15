#include <stdio.h>
#include <stdlib.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>



die(char *message)
{
    printf("%s\n", message);
    exit(1);
}


int demux(char *filename)
{
    printf("demuxing: %s\n", filename);

   
    av_register_all();


    AVFormatContext *context = avformat_alloc_context();
    printf("allocated format context: %x\n", context);

    if (avformat_open_input(&context, filename, NULL, NULL) < 0)
        die("could not open input video");

    if (avformat_find_stream_info(context, NULL) < 0)
        die("could not find file info");


    printf("parsing input\n");

    int count;
    AVPacket packet;
    while (1) {
        if (av_read_frame(context, &packet) < 0)
            break;
        count ++;
    }

    printf("total packet count: %i\n", count);


    avformat_close_input(&context);


    return 0;
}


int main(int argc, char* argv[])
{
    if (argc < 2)
        die("usage: video_demux <input video>");

    return demux(argv[1]);
}

