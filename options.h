#ifndef _OPTIONS_H
#define _OPTIONS_H

#include <vector>
#include <map>
#include <stdint.h>
#include "libsndfilesrc.h"
#include "flacsrc.h"
#include "wvpacksrc.h"
#include "itunetags.h"

struct Options {
    enum { kABR, kTVBR, kCVBR, kCBR };

    Options() :
	output_format(0),
	method(-1), bitrate(-1), quality(2), rate(-1),
	ifilename(0), ofilename(0), outdir(0), downmix(-1),
	verbose(true), is_raw(false), is_first_file(true),
	save_stat(false), is_adts(false), nice(false),
	ignore_length(false), no_optimize(false),
	raw_channels(2), raw_sample_rate(44100),
	raw_format(L"S16LE"),
	sleep(0)
    {}
    bool parse(int &argc, wchar_t **&argv);

    bool isAAC() const
    {
	return output_format == 'aac ' || output_format == 'aach';
    }
    bool isSBR() const
    {
	return output_format == 'aach';
    }
    bool isALAC() const
    {
	return output_format == 'alac';
    }
    bool isLPCM() const
    {
	return output_format == 'lpcm';
    }

    uint32_t output_format;
    int32_t method;
    uint32_t bitrate, quality;
    uint32_t raw_channels, raw_sample_rate;
    uint32_t sleep;
    int rate; /* -1: keep, 0: auto, others: literal value */
    int downmix; /* -1: none, 1: mono, 2: stereo */
    wchar_t *ifilename, *ofilename, *outdir, *raw_format;
    bool verbose, is_raw, is_first_file, is_adts, save_stat,
	 nice, ignore_length, no_optimize;
    std::vector<std::string> used_settings;
    std::vector<int> sample_rate_table;
    std::map<uint32_t, std::wstring> tagopts;
    std::wstring encoder_name;

    LibSndfileModule libsndfile;
    FLACModule libflac;
    WavpackModule libwavpack;
    LibID3TagModule libid3tag;
};

#endif
