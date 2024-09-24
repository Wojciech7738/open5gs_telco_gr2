libmac_sources = files('''
    mac_messages.h
    mac_messages.c

    message.h
    message.c

    decoder.h
    decoder.c

    encoder.h
    encoder.c

    mac_buffer.h
    mac_buffer.c

    pdu_handler.h
    pdu_handler.c
'''.split())

libmac = static_library('mac',
    sources : libmac_sources,
    dependencies : [libmetrics_dep,
                    libcore_dep],
    install : false)

libmac_dep = declare_dependency(
    link_with : libmac,
    dependencies : [libmetrics_dep,
                    libcore_dep])

mac_sources = files('''
    app.c
    ../main.c
'''.split())

executable('open5gs-macd',
    sources : mac_sources,
    c_args : '-DDEFAULT_CONFIG_FILENAME="@0@/amf.yaml"'.format(open5gs_sysconfdir),
    include_directories : srcinc,
    dependencies : libmac_dep,
    install_rpath : libdir,
    install : true)
