{
'target_defaults': {
  'cflags': [
    '-std=c++11',
    '-Wall',
    '-Werror',
    '-Wshadow',
    '-Wno-comment',
    '-g',
    '-rdynamic',
  ]
},
'targets': [
  {
    'target_name': 'snakes',
    'type': 'executable',
    'sources': [
      'snakes.cc'
    ],
    'libraries': ["-lglut", "-lGLU", "-lGL"],
  },
]
}
