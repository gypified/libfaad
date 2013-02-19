# This file is used with the GYP meta build system.
# http://code.google.com/p/gyp
# To build try this:
#   svn co http://gyp.googlecode.com/svn/trunk gyp
#   ./gyp/gyp -f make --depth=. libfaad2.gyp
#   make
#   ./out/Debug/test

{
  'variables': {
    'target_arch%': 'ia32', # built for a 32-bit CPU by default
  },
  'target_defaults': {
    'default_configuration': 'Debug',
    'configurations': {
      'Debug': {
        'defines': [ 'DEBUG', '_DEBUG' ],
        'msvs_settings': {
          'VCCLCompilerTool': {
            'RuntimeLibrary': 1, # static debug
          },
        },
      },
      'Release': {
        'defines': [ 'NDEBUG' ],
        'msvs_settings': {
          'VCCLCompilerTool': {
            'RuntimeLibrary': 0, # static release
          },
        },
      }
    },
    'msvs_settings': {
      'VCLinkerTool': {
        'GenerateDebugInformation': 'true',
      },
    },
    'conditions': [
      ['OS=="mac"', {
        'conditions': [
          ['target_arch=="ia32"', { 'xcode_settings': { 'ARCHS': [ 'i386' ] } }],
          ['target_arch=="x64"', { 'xcode_settings': { 'ARCHS': [ 'x86_64' ] } }]
        ],
      }],
    ]
  },

  'targets': [
    {
      'target_name': 'faad2',
      'product_prefix': 'lib',
      'type': 'static_library',
      'sources': [
        'libfaad/bits.c',
        'libfaad/cfft.c',
        'libfaad/decoder.c',
        'libfaad/drc.c',
        'libfaad/drm_dec.c',
        'libfaad/error.c',
        'libfaad/filtbank.c',
        'libfaad/ic_predict.c',
        'libfaad/is.c',
        'libfaad/lt_predict.c',
        'libfaad/mdct.c',
        'libfaad/mp4.c',
        'libfaad/ms.c',
        'libfaad/output.c',
        'libfaad/pns.c',
        'libfaad/ps_dec.c',
        'libfaad/ps_syntax.c',
        'libfaad/pulse.c',
        'libfaad/specrec.c',
        'libfaad/syntax.c',
        'libfaad/tns.c',
        'libfaad/hcr.c',
        'libfaad/huffman.c',
        'libfaad/rvlc.c',
        'libfaad/ssr.c',
        'libfaad/ssr_fb.c',
        'libfaad/ssr_ipqf.c',
        'libfaad/common.c',
        'libfaad/sbr_dct.c',
        'libfaad/sbr_e_nf.c',
        'libfaad/sbr_fbt.c',
        'libfaad/sbr_hfadj.c',
        'libfaad/sbr_hfgen.c',
        'libfaad/sbr_huff.c',
        'libfaad/sbr_qmf.c',
        'libfaad/sbr_syntax.c',
        'libfaad/sbr_tf_grid.c',
        'libfaad/sbr_dec.c'
      ],
      'defines': [
        'PIC',
        'HAVE_CONFIG_H',
      ],
      'include_dirs': [
        # platform and arch-specific headers
        'config/<(OS)/<(target_arch)',
        'include',
      ],
      'direct_dependent_settings': {
        'include_dirs': [
          # platform and arch-specific headers
          'config/<(OS)/<(target_arch)',
          'include',
        ],
      },
    },

    {
      'target_name': 'test',
      'type': 'executable',
      'dependencies': [ 'faad2' ],
      'sources': [ 'test.c' ]
    },
  ]
}
