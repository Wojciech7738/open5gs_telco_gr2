librrcrec_sources = files(
  'handler.c'
)

librrcrec_inc = include_directories('.')

librrcrec = static_library('RRC_reconfiguration',
    sources : librrcrec_sources,
    include_directories : librrcrec_inc,
    dependencies : libcore_dep,
    install : false
)

librrcrec_dep = declare_dependency(
    link_with : librrcrec,
    include_directories : [librrcrec_inc, srcinc],
)
