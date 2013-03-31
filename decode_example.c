/**
 * Example file that decodes raw AAC data from stdin,
 * and outputs the PCM audio data to stdout.
 */

#include <neaacdec.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
  unsigned char input[1024];
  void *output;

  size_t input_size = 0;

  NeAACDecFrameInfo hInfo;
  memset(&hInfo, 0, sizeof hInfo);

  // create decoder handle
  NeAACDecHandle hAac = NeAACDecOpen();

  // Get the current config
  NeAACDecConfigurationPtr conf = NeAACDecGetCurrentConfiguration(hAac);

  // XXX: If needed change some of the values in conf

  // Set the new configuration
  NeAACDecSetConfiguration(hAac, conf);

  // read the first buffer... will be used in `NeAACDecInit()` call...
  input_size = fread(input, 1, sizeof input, stdin);
  fprintf(stderr, "read %d bytes\n", (int)input_size);

  // Initialise the library using one of the initialization functions
  int done = 0;
  unsigned long samplerate;
  unsigned char channels;
  char err = NeAACDecInit(hAac, input, input_size, &samplerate, &channels);
  if (err != 0) {
    // Handle error
    fprintf(stderr, "NeAACDecInit error: %d\n", err);
    abort();
  }
  fprintf(stderr, "{ samplerate: %lu, channels: %u, bytesRead: %d }\n", samplerate, channels, err);

  // Loop until decoding finished
  unsigned char *cur = input + err;
  input_size -= err;

  do {
    do {
      fprintf(stderr, "decoding data\n");

      // Decode the frame in buffer
      output = NeAACDecDecode(hAac, &hInfo, cur, input_size);

      if ((hInfo.error == 0) && (hInfo.samples > 0)) {
        // do what you need to do with the decoded samples
        fprintf(stderr, "decoded %lu samples\n", hInfo.samples);
        fprintf(stderr, "  bytesconsumed: %lu\n", hInfo.bytesconsumed);
        fprintf(stderr, "  channels: %d\n", hInfo.channels);
        fprintf(stderr, "  samplerate: %lu\n", hInfo.samplerate);
        fprintf(stderr, "  sbr: %u\n", hInfo.sbr);
        fprintf(stderr, "  object_type: %u\n", hInfo.object_type);
        fprintf(stderr, "  header_type: %u\n", hInfo.header_type);
        fprintf(stderr, "  num_front_channels: %u\n", hInfo.num_front_channels);
        fprintf(stderr, "  num_side_channels: %u\n", hInfo.num_side_channels);
        fprintf(stderr, "  num_back_channels: %u\n", hInfo.num_back_channels);
        fprintf(stderr, "  num_lfe_channels: %u\n", hInfo.num_lfe_channels);
        fprintf(stderr, "  ps: %u\n", hInfo.ps);
        fprintf(stderr, "\n");

      } else if (hInfo.error != 0) {
        // Some error occurred while decoding this frame
        fprintf(stderr, "NeAACDecode error: %d\n", hInfo.error);
        fprintf(stderr, "%s\n", NeAACDecGetErrorMessage(hInfo.error));
        abort();
      } else {
        fprintf(stderr, "got nothing...\n");
      }

      cur += hInfo.bytesconsumed;
      input_size -= hInfo.bytesconsumed;
      fprintf(stderr, "%p %zd\n", cur, input_size);
    } while (!done);

    // Put next frame in buffer
    fprintf(stderr, "reading from stdin\n");
    input_size = fread(input, 1, sizeof input, stdin);
    cur = input;
  } while (!done);

  NeAACDecClose(hAac);
}
