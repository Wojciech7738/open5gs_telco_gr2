
libauth_sources = files(
  'l3_modules.c',
  'auth_response.c')

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