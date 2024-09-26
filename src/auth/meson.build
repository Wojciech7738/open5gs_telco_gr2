
libauth_sources = files(
  'l3_modules.c',
  'l3_modules.h',
  'auth_request.c',
  'auth_request.h',
  'auth_response.c',
  'auth_response.h',
  'authentication_messages.h',
  'authorization_messages.h',
  'common.h',
  'common.c',
  'DedicatedNAS-Message.h',
  )

libauth_inc = include_directories('.')

libauth = static_library('AUTH',
    sources : libauth_sources,
    include_directories : libauth_inc,
    dependencies : libcore_dep,
    install : false
)

libauth_dep = declare_dependency(
    link_with : libauth,
    include_directories : [libauth_inc, srcinc],
)