# Copyright (C) 2019 by Sukchan Lee <acetcom@gmail.com>

# This file is part of Open5GS.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

testunit_mac_sources = files('''
    mac-test.c
    abts-main.c
'''.split())

testunit_mac_cc_flags = []
if cc.get_id() == 'gcc' or cc.get_id() == 'clang'
    testunit_mac_cc_flags += cc.get_supported_arguments([
                    '-Wno-missing-prototypes',
                    '-Wno-missing-declarations',
                    '-Wno-discarded-qualifiers',
                    '-Wno-incompatible-pointer-types',
                    '-Wno-unused-variable',
                    '-Wno-deprecated-declarations'])
endif

macinc = include_directories('../../src/mac')

testunit_mac_exe = executable('core',
    sources : testunit_mac_sources,
    c_args : testunit_mac_cc_flags,
    include_directories : macinc,
    dependencies : libmac_dep)

test('mac', testunit_mac_exe, is_parallel : false, suite: 'unit')
