
libauth_sources = files(
  'auth_request.h',
  'auth_response.h',
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