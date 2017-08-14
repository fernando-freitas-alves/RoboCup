## Makefile.am for pursuit server

## define the program that has to be built and the related sources
bin_PROGRAMS = trilearn_player trilearn_coach

AM_CXXFLAGS=-std=c++1y -stdlib=libc++ -mmacosx-version-min=10.9
AM_LDFLAGS=-lboost_system$(BOOST_LIB_SUFFIX)
# AM_CPPFLAGS=-I$NEAT
AM_CPPFLAGS=-I/usr/local/include -pthread
AM_LDFLAGS+=-L/usr/local/lib `pkg-config --libs grpc++ grpc`       \
            -lgrpc++_reflection \
            -lprotobuf -lpthread -ldl

SOURCES =         Connection.cpp \
        SenseHandler.cpp \
        ActHandler.cpp \
        SoccerTypes.cpp \
        Objects.cpp \
        WorldModel.cpp \
        WorldModelHighLevel.cpp \
        WorldModelPredict.cpp \
        WorldModelUpdate.cpp \
        ServerSettings.cpp \
        PlayerSettings.cpp \
        GenericValues.cpp \
        Formations.cpp \
        Geometry.cpp \
        Parse.cpp \
        Logger.cpp \
	Connection.h \
        SenseHandler.h \
        ActHandler.h \
        SoccerTypes.h \
        Objects.h \
        WorldModel.h \
        ServerSettings.h \
        PlayerSettings.h \
        GenericValues.h \
        Formations.h \
        Geometry.h \
        Parse.h \
        Logger.h

trilearn_player_SOURCES = ${SOURCES}    \
        BasicPlayer.cpp \
        Player.cpp \
        PlayerTeams.cpp \
        main.cpp \
        BasicPlayer.h \
        Player.h \
        Utilities.h \
        Utilities.cpp \
        NEAT/Assert.h \
        NEAT/Genes.h \
        NEAT/Genome.cpp \
        NEAT/Genome.h \
        NEAT/Innovation.cpp \
        NEAT/Innovation.h \
        NEAT/NEAT.cpp \
        NEAT/NEAT.h \
        NEAT/NeuralNetwork.cpp \
        NEAT/NeuralNetwork.h \
        NEAT/Parameters.cpp \
        NEAT/Parameters.h \
        NEAT/PhenotypeBehavior.cpp \
        NEAT/PhenotypeBehavior.h \
        NEAT/Population.cpp \
        NEAT/Population.h \
        NEAT/PythonBindings.cpp \
        NEAT/PythonBindings.h \
        NEAT/Random.cpp \
        NEAT/Random.h \
        NEAT/Species.cpp \
        NEAT/Species.h \
        NEAT/Substrate.cpp \
        NEAT/Substrate.h \
        NEAT/Traits.cpp \
        NEAT/Traits.h \
        NEAT/Utils.cpp \
        NEAT/Utils.h \
        pbrpc/ControllerRPC.hh \
        pbrpc/ControllerRPC.hh.gch \
        pbrpc/MethodRPC.hh \
        pbrpc/MethodRPC.hh.gch \
        pbrpc/ServiceManager.cc \
        pbrpc/ServiceManager.hh \
        pbrpc/ServiceManager.hh.gch \
        pbrpc/ServiceRPC.hh \
        pbrpc/ServiceRPC.hh.gch \
        pbrpc/config.h \
        pbrpc/config.h.gch \
        pbrpc/pbrpc.pb.cc \
        pbrpc/pbrpc.pb.h \
        pbrpc/pbrpc.pb.h.gch \
        pbrpc/pbrpc.proto \
        pbrpc/pbrpc_export.h \
        pbrpc/pbrpc_export.h.gch
 #\
        # rpc/detail/all.h \
        # rpc/detail/any.h \
        # rpc/detail/async_writer.h \
        # rpc/detail/bool.h \
        # rpc/detail/call.h \
        # rpc/detail/client_error.h \
        # rpc/detail/constant.h \
        # rpc/detail/dev_utils.h \
        # rpc/detail/func_tools.h \
        # rpc/detail/func_traits.h \
        # rpc/detail/if.h \
        # rpc/detail/invoke.h \
        # rpc/detail/is_specialization_of.h \
        # rpc/detail/log.h \
        # rpc/detail/make_unique.h \
        # rpc/detail/not.h \
        # rpc/detail/pimpl.h \
        # rpc/detail/response.h \
        # rpc/detail/server_session.h \
        # rpc/detail/thread_group.h \
        # rpc/detail/util.h \
        # rpc/msgpack/cpp_config.hpp \
        # rpc/msgpack/fbuffer.h \
        # rpc/msgpack/fbuffer.hpp \
        # rpc/msgpack/gcc_atomic.h \
        # rpc/msgpack/iterator.hpp \
        # rpc/msgpack/meta.hpp \
        # rpc/msgpack/object.h \
        # rpc/msgpack/object.hpp \
        # rpc/msgpack/object_fwd.hpp \
        # rpc/msgpack/pack.h \
        # rpc/msgpack/pack.hpp \
        # rpc/msgpack/pack_define.h \
        # rpc/msgpack/pack_template.h \
        # rpc/msgpack/predef.h \
        # rpc/msgpack/preprocessor.hpp \
        # rpc/msgpack/sbuffer.h \
        # rpc/msgpack/sbuffer.hpp \
        # rpc/msgpack/sysdep.h \
        # rpc/msgpack/type.hpp \
        # rpc/msgpack/unpack.h \
        # rpc/msgpack/unpack.hpp \
        # rpc/msgpack/unpack_define.h \
        # rpc/msgpack/unpack_template.h \
        # rpc/msgpack/util.h \
        # rpc/msgpack/version.h \
        # rpc/msgpack/version.hpp \
        # rpc/msgpack/version_master.h \
        # rpc/msgpack/versioning.hpp \
        # rpc/msgpack/vrefbuffer.h \
        # rpc/msgpack/vrefbuffer.hpp \
        # rpc/msgpack/zbuffer.h \
        # rpc/msgpack/zbuffer.hpp \
        # rpc/msgpack/zone.h \
        # rpc/msgpack/zone.hpp \
        # rpc/msgpack/adaptor/adaptor_base.hpp \
        # rpc/msgpack/adaptor/array_ref.hpp \
        # rpc/msgpack/adaptor/bool.hpp \
        # rpc/msgpack/adaptor/char_ptr.hpp \
        # rpc/msgpack/adaptor/check_container_size.hpp \
        # rpc/msgpack/adaptor/define.hpp \
        # rpc/msgpack/adaptor/deque.hpp \
        # rpc/msgpack/adaptor/ext.hpp \
        # rpc/msgpack/adaptor/fixint.hpp \
        # rpc/msgpack/adaptor/float.hpp \
        # rpc/msgpack/adaptor/int.hpp \
        # rpc/msgpack/adaptor/list.hpp \
        # rpc/msgpack/adaptor/map.hpp \
        # rpc/msgpack/adaptor/msgpack_tuple.hpp \
        # rpc/msgpack/adaptor/nil.hpp \
        # rpc/msgpack/adaptor/pair.hpp \
        # rpc/msgpack/adaptor/raw.hpp \
        # rpc/msgpack/adaptor/set.hpp \
        # rpc/msgpack/adaptor/string.hpp \
        # rpc/msgpack/adaptor/v4raw.hpp \
        # rpc/msgpack/adaptor/vector.hpp \
        # rpc/msgpack/adaptor/vector_bool.hpp \
        # rpc/msgpack/adaptor/vector_char.hpp \
        # rpc/msgpack/adaptor/vector_unsigned_char.hpp \
        # rpc/msgpack/adaptor/boost/fusion.hpp \
        # rpc/msgpack/adaptor/boost/msgpack_variant.hpp \
        # rpc/msgpack/adaptor/boost/optional.hpp \
        # rpc/msgpack/adaptor/boost/string_ref.hpp \
        # rpc/msgpack/adaptor/cpp11/array.hpp \
        # rpc/msgpack/adaptor/cpp11/array_char.hpp \
        # rpc/msgpack/adaptor/cpp11/array_unsigned_char.hpp \
        # rpc/msgpack/adaptor/cpp11/forward_list.hpp \
        # rpc/msgpack/adaptor/cpp11/shared_ptr.hpp \
        # rpc/msgpack/adaptor/cpp11/tuple.hpp \
        # rpc/msgpack/adaptor/cpp11/unique_ptr.hpp \
        # rpc/msgpack/adaptor/cpp11/unordered_map.hpp \
        # rpc/msgpack/adaptor/cpp11/unordered_set.hpp \
        # rpc/msgpack/adaptor/detail/cpp03_define_array.hpp \
        # rpc/msgpack/adaptor/detail/cpp03_define_map.hpp \
        # rpc/msgpack/adaptor/detail/cpp03_msgpack_tuple.hpp \
        # rpc/msgpack/adaptor/detail/cpp11_define_array.hpp \
        # rpc/msgpack/adaptor/detail/cpp11_define_map.hpp \
        # rpc/msgpack/adaptor/detail/cpp11_msgpack_tuple.hpp \
        # rpc/msgpack/adaptor/tr1/unordered_map.hpp \
        # rpc/msgpack/adaptor/tr1/unordered_set.hpp \
        # rpc/msgpack/detail/cpp03_zone.hpp \
        # rpc/msgpack/detail/cpp11_zone.hpp \
        # rpc/msgpack/predef/architecture.h \
        # rpc/msgpack/predef/compiler.h \
        # rpc/msgpack/predef/language.h \
        # rpc/msgpack/predef/library.h \
        # rpc/msgpack/predef/make.h \
        # rpc/msgpack/predef/os.h \
        # rpc/msgpack/predef/other.h \
        # rpc/msgpack/predef/platform.h \
        # rpc/msgpack/predef/version.h \
        # rpc/msgpack/predef/version_number.h \
        # rpc/msgpack/predef/architecture/alpha.h \
        # rpc/msgpack/predef/architecture/arm.h \
        # rpc/msgpack/predef/architecture/blackfin.h \
        # rpc/msgpack/predef/architecture/convex.h \
        # rpc/msgpack/predef/architecture/ia64.h \
        # rpc/msgpack/predef/architecture/m68k.h \
        # rpc/msgpack/predef/architecture/mips.h \
        # rpc/msgpack/predef/architecture/parisc.h \
        # rpc/msgpack/predef/architecture/ppc.h \
        # rpc/msgpack/predef/architecture/pyramid.h \
        # rpc/msgpack/predef/architecture/rs6k.h \
        # rpc/msgpack/predef/architecture/sparc.h \
        # rpc/msgpack/predef/architecture/superh.h \
        # rpc/msgpack/predef/architecture/sys370.h \
        # rpc/msgpack/predef/architecture/sys390.h \
        # rpc/msgpack/predef/architecture/x86.h \
        # rpc/msgpack/predef/architecture/z.h \
        # rpc/msgpack/predef/architecture/x86/32.h \
        # rpc/msgpack/predef/architecture/x86/64.h \
        # rpc/msgpack/predef/compiler/borland.h \
        # rpc/msgpack/predef/compiler/clang.h \
        # rpc/msgpack/predef/compiler/comeau.h \
        # rpc/msgpack/predef/compiler/compaq.h \
        # rpc/msgpack/predef/compiler/diab.h \
        # rpc/msgpack/predef/compiler/digitalmars.h \
        # rpc/msgpack/predef/compiler/dignus.h \
        # rpc/msgpack/predef/compiler/edg.h \
        # rpc/msgpack/predef/compiler/ekopath.h \
        # rpc/msgpack/predef/compiler/gcc.h \
        # rpc/msgpack/predef/compiler/gcc_xml.h \
        # rpc/msgpack/predef/compiler/greenhills.h \
        # rpc/msgpack/predef/compiler/hp_acc.h \
        # rpc/msgpack/predef/compiler/iar.h \
        # rpc/msgpack/predef/compiler/ibm.h \
        # rpc/msgpack/predef/compiler/intel.h \
        # rpc/msgpack/predef/compiler/kai.h \
        # rpc/msgpack/predef/compiler/llvm.h \
        # rpc/msgpack/predef/compiler/metaware.h \
        # rpc/msgpack/predef/compiler/metrowerks.h \
        # rpc/msgpack/predef/compiler/microtec.h \
        # rpc/msgpack/predef/compiler/mpw.h \
        # rpc/msgpack/predef/compiler/palm.h \
        # rpc/msgpack/predef/compiler/pgi.h \
        # rpc/msgpack/predef/compiler/sgi_mipspro.h \
        # rpc/msgpack/predef/compiler/sunpro.h \
        # rpc/msgpack/predef/compiler/tendra.h \
        # rpc/msgpack/predef/compiler/visualc.h \
        # rpc/msgpack/predef/compiler/watcom.h \
        # rpc/msgpack/predef/detail/_cassert.h \
        # rpc/msgpack/predef/detail/_exception.h \
        # rpc/msgpack/predef/detail/comp_detected.h \
        # rpc/msgpack/predef/detail/endian_compat.h \
        # rpc/msgpack/predef/detail/os_detected.h \
        # rpc/msgpack/predef/detail/platform_detected.h \
        # rpc/msgpack/predef/detail/test.h \
        # rpc/msgpack/predef/language/objc.h \
        # rpc/msgpack/predef/language/stdc.h \
        # rpc/msgpack/predef/language/stdcpp.h \
        # rpc/msgpack/predef/library/c.h \
        # rpc/msgpack/predef/library/std.h \
        # rpc/msgpack/predef/library/c/_prefix.h \
        # rpc/msgpack/predef/library/c/gnu.h \
        # rpc/msgpack/predef/library/c/uc.h \
        # rpc/msgpack/predef/library/c/vms.h \
        # rpc/msgpack/predef/library/c/zos.h \
        # rpc/msgpack/predef/library/std/_prefix.h \
        # rpc/msgpack/predef/library/std/cxx.h \
        # rpc/msgpack/predef/library/std/dinkumware.h \
        # rpc/msgpack/predef/library/std/libcomo.h \
        # rpc/msgpack/predef/library/std/modena.h \
        # rpc/msgpack/predef/library/std/msl.h \
        # rpc/msgpack/predef/library/std/roguewave.h \
        # rpc/msgpack/predef/library/std/sgi.h \
        # rpc/msgpack/predef/library/std/stdcpp3.h \
        # rpc/msgpack/predef/library/std/stlport.h \
        # rpc/msgpack/predef/library/std/vacpp.h \
        # rpc/msgpack/predef/os/aix.h \
        # rpc/msgpack/predef/os/amigaos.h \
        # rpc/msgpack/predef/os/android.h \
        # rpc/msgpack/predef/os/beos.h \
        # rpc/msgpack/predef/os/bsd.h \
        # rpc/msgpack/predef/os/cygwin.h \
        # rpc/msgpack/predef/os/haiku.h \
        # rpc/msgpack/predef/os/hpux.h \
        # rpc/msgpack/predef/os/ios.h \
        # rpc/msgpack/predef/os/irix.h \
        # rpc/msgpack/predef/os/linux.h \
        # rpc/msgpack/predef/os/macos.h \
        # rpc/msgpack/predef/os/os400.h \
        # rpc/msgpack/predef/os/qnxnto.h \
        # rpc/msgpack/predef/os/solaris.h \
        # rpc/msgpack/predef/os/unix.h \
        # rpc/msgpack/predef/os/vms.h \
        # rpc/msgpack/predef/os/windows.h \
        # rpc/msgpack/predef/os/bsd/bsdi.h \
        # rpc/msgpack/predef/os/bsd/dragonfly.h \
        # rpc/msgpack/predef/os/bsd/free.h \
        # rpc/msgpack/predef/os/bsd/net.h \
        # rpc/msgpack/predef/os/bsd/open.h \
        # rpc/msgpack/predef/other/endian.h \
        # rpc/msgpack/predef/platform/mingw.h \
        # rpc/msgpack/predef/platform/windows_desktop.h \
        # rpc/msgpack/predef/platform/windows_phone.h \
        # rpc/msgpack/predef/platform/windows_runtime.h \
        # rpc/msgpack/predef/platform/windows_store.h \
        # rpc/msgpack/preprocessor/arithmetic.hpp \
        # rpc/msgpack/preprocessor/array.hpp \
        # rpc/msgpack/preprocessor/assert_msg.hpp \
        # rpc/msgpack/preprocessor/cat.hpp \
        # rpc/msgpack/preprocessor/comma.hpp \
        # rpc/msgpack/preprocessor/comma_if.hpp \
        # rpc/msgpack/preprocessor/comparison.hpp \
        # rpc/msgpack/preprocessor/control.hpp \
        # rpc/msgpack/preprocessor/debug.hpp \
        # rpc/msgpack/preprocessor/dec.hpp \
        # rpc/msgpack/preprocessor/empty.hpp \
        # rpc/msgpack/preprocessor/enum.hpp \
        # rpc/msgpack/preprocessor/enum_params.hpp \
        # rpc/msgpack/preprocessor/enum_params_with_a_default.hpp \
        # rpc/msgpack/preprocessor/enum_params_with_defaults.hpp \
        # rpc/msgpack/preprocessor/enum_shifted.hpp \
        # rpc/msgpack/preprocessor/enum_shifted_params.hpp \
        # rpc/msgpack/preprocessor/expand.hpp \
        # rpc/msgpack/preprocessor/expr_if.hpp \
        # rpc/msgpack/preprocessor/facilities.hpp \
        # rpc/msgpack/preprocessor/for.hpp \
        # rpc/msgpack/preprocessor/identity.hpp \
        # rpc/msgpack/preprocessor/if.hpp \
        # rpc/msgpack/preprocessor/inc.hpp \
        # rpc/msgpack/preprocessor/iterate.hpp \
        # rpc/msgpack/preprocessor/iteration.hpp \
        # rpc/msgpack/preprocessor/library.hpp \
        # rpc/msgpack/preprocessor/limits.hpp \
        # rpc/msgpack/preprocessor/list.hpp \
        # rpc/msgpack/preprocessor/logical.hpp \
        # rpc/msgpack/preprocessor/max.hpp \
        # rpc/msgpack/preprocessor/min.hpp \
        # rpc/msgpack/preprocessor/punctuation.hpp \
        # rpc/msgpack/preprocessor/repeat.hpp \
        # rpc/msgpack/preprocessor/repeat_2nd.hpp \
        # rpc/msgpack/preprocessor/repeat_3rd.hpp \
        # rpc/msgpack/preprocessor/repeat_from_to.hpp \
        # rpc/msgpack/preprocessor/repeat_from_to_2nd.hpp \
        # rpc/msgpack/preprocessor/repeat_from_to_3rd.hpp \
        # rpc/msgpack/preprocessor/repetition.hpp \
        # rpc/msgpack/preprocessor/selection.hpp \
        # rpc/msgpack/preprocessor/seq.hpp \
        # rpc/msgpack/preprocessor/slot.hpp \
        # rpc/msgpack/preprocessor/stringize.hpp \
        # rpc/msgpack/preprocessor/tuple.hpp \
        # rpc/msgpack/preprocessor/variadic.hpp \
        # rpc/msgpack/preprocessor/while.hpp \
        # rpc/msgpack/preprocessor/wstringize.hpp \
        # rpc/msgpack/preprocessor/arithmetic/add.hpp \
        # rpc/msgpack/preprocessor/arithmetic/dec.hpp \
        # rpc/msgpack/preprocessor/arithmetic/div.hpp \
        # rpc/msgpack/preprocessor/arithmetic/inc.hpp \
        # rpc/msgpack/preprocessor/arithmetic/mod.hpp \
        # rpc/msgpack/preprocessor/arithmetic/mul.hpp \
        # rpc/msgpack/preprocessor/arithmetic/sub.hpp \
        # rpc/msgpack/preprocessor/arithmetic/detail/div_base.hpp \
        # rpc/msgpack/preprocessor/array/data.hpp \
        # rpc/msgpack/preprocessor/array/elem.hpp \
        # rpc/msgpack/preprocessor/array/enum.hpp \
        # rpc/msgpack/preprocessor/array/insert.hpp \
        # rpc/msgpack/preprocessor/array/pop_back.hpp \
        # rpc/msgpack/preprocessor/array/pop_front.hpp \
        # rpc/msgpack/preprocessor/array/push_back.hpp \
        # rpc/msgpack/preprocessor/array/push_front.hpp \
        # rpc/msgpack/preprocessor/array/remove.hpp \
        # rpc/msgpack/preprocessor/array/replace.hpp \
        # rpc/msgpack/preprocessor/array/reverse.hpp \
        # rpc/msgpack/preprocessor/array/size.hpp \
        # rpc/msgpack/preprocessor/array/to_list.hpp \
        # rpc/msgpack/preprocessor/array/to_seq.hpp \
        # rpc/msgpack/preprocessor/array/to_tuple.hpp \
        # rpc/msgpack/preprocessor/array/detail/get_data.hpp \
        # rpc/msgpack/preprocessor/comparison/equal.hpp \
        # rpc/msgpack/preprocessor/comparison/greater.hpp \
        # rpc/msgpack/preprocessor/comparison/greater_equal.hpp \
        # rpc/msgpack/preprocessor/comparison/less.hpp \
        # rpc/msgpack/preprocessor/comparison/less_equal.hpp \
        # rpc/msgpack/preprocessor/comparison/not_equal.hpp \
        # rpc/msgpack/preprocessor/config/config.hpp \
        # rpc/msgpack/preprocessor/config/limits.hpp \
        # rpc/msgpack/preprocessor/control/deduce_d.hpp \
        # rpc/msgpack/preprocessor/control/expr_if.hpp \
        # rpc/msgpack/preprocessor/control/expr_iif.hpp \
        # rpc/msgpack/preprocessor/control/if.hpp \
        # rpc/msgpack/preprocessor/control/iif.hpp \
        # rpc/msgpack/preprocessor/control/while.hpp \
        # rpc/msgpack/preprocessor/control/detail/while.hpp \
        # rpc/msgpack/preprocessor/control/detail/dmc/while.hpp \
        # rpc/msgpack/preprocessor/control/detail/edg/while.hpp \
        # rpc/msgpack/preprocessor/control/detail/msvc/while.hpp \
        # rpc/msgpack/preprocessor/debug/assert.hpp \
        # rpc/msgpack/preprocessor/debug/error.hpp \
        # rpc/msgpack/preprocessor/debug/line.hpp \
        # rpc/msgpack/preprocessor/detail/auto_rec.hpp \
        # rpc/msgpack/preprocessor/detail/check.hpp \
        # rpc/msgpack/preprocessor/detail/is_binary.hpp \
        # rpc/msgpack/preprocessor/detail/is_nullary.hpp \
        # rpc/msgpack/preprocessor/detail/is_unary.hpp \
        # rpc/msgpack/preprocessor/detail/null.hpp \
        # rpc/msgpack/preprocessor/detail/split.hpp \
        # rpc/msgpack/preprocessor/detail/dmc/auto_rec.hpp \
        # rpc/msgpack/preprocessor/facilities/apply.hpp \
        # rpc/msgpack/preprocessor/facilities/empty.hpp \
        # rpc/msgpack/preprocessor/facilities/expand.hpp \
        # rpc/msgpack/preprocessor/facilities/identity.hpp \
        # rpc/msgpack/preprocessor/facilities/intercept.hpp \
        # rpc/msgpack/preprocessor/facilities/is_1.hpp \
        # rpc/msgpack/preprocessor/facilities/is_empty.hpp \
        # rpc/msgpack/preprocessor/facilities/is_empty_or_1.hpp \
        # rpc/msgpack/preprocessor/facilities/is_empty_variadic.hpp \
        # rpc/msgpack/preprocessor/facilities/overload.hpp \
        # rpc/msgpack/preprocessor/facilities/detail/is_empty.hpp \
        # rpc/msgpack/preprocessor/iteration/iterate.hpp \
        # rpc/msgpack/preprocessor/iteration/local.hpp \
        # rpc/msgpack/preprocessor/iteration/self.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/finish.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/local.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/rlocal.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/self.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/start.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/lower1.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/lower2.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/lower3.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/lower4.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/lower5.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/upper1.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/upper2.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/upper3.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/upper4.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/upper5.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/forward1.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/forward2.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/forward3.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/forward4.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/forward5.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/reverse1.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/reverse2.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/reverse3.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/reverse4.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/reverse5.hpp \
        # rpc/msgpack/preprocessor/list/adt.hpp \
        # rpc/msgpack/preprocessor/list/append.hpp \
        # rpc/msgpack/preprocessor/list/at.hpp \
        # rpc/msgpack/preprocessor/list/cat.hpp \
        # rpc/msgpack/preprocessor/list/enum.hpp \
        # rpc/msgpack/preprocessor/list/filter.hpp \
        # rpc/msgpack/preprocessor/list/first_n.hpp \
        # rpc/msgpack/preprocessor/list/fold_left.hpp \
        # rpc/msgpack/preprocessor/list/fold_right.hpp \
        # rpc/msgpack/preprocessor/list/for_each.hpp \
        # rpc/msgpack/preprocessor/list/for_each_i.hpp \
        # rpc/msgpack/preprocessor/list/for_each_product.hpp \
        # rpc/msgpack/preprocessor/list/rest_n.hpp \
        # rpc/msgpack/preprocessor/list/reverse.hpp \
        # rpc/msgpack/preprocessor/list/size.hpp \
        # rpc/msgpack/preprocessor/list/to_array.hpp \
        # rpc/msgpack/preprocessor/list/to_seq.hpp \
        # rpc/msgpack/preprocessor/list/to_tuple.hpp \
        # rpc/msgpack/preprocessor/list/transform.hpp \
        # rpc/msgpack/preprocessor/list/detail/fold_left.hpp \
        # rpc/msgpack/preprocessor/list/detail/fold_right.hpp \
        # rpc/msgpack/preprocessor/list/detail/dmc/fold_left.hpp \
        # rpc/msgpack/preprocessor/list/detail/edg/fold_left.hpp \
        # rpc/msgpack/preprocessor/list/detail/edg/fold_right.hpp \
        # rpc/msgpack/preprocessor/logical/and.hpp \
        # rpc/msgpack/preprocessor/logical/bitand.hpp \
        # rpc/msgpack/preprocessor/logical/bitnor.hpp \
        # rpc/msgpack/preprocessor/logical/bitor.hpp \
        # rpc/msgpack/preprocessor/logical/bitxor.hpp \
        # rpc/msgpack/preprocessor/logical/bool.hpp \
        # rpc/msgpack/preprocessor/logical/compl.hpp \
        # rpc/msgpack/preprocessor/logical/nor.hpp \
        # rpc/msgpack/preprocessor/logical/not.hpp \
        # rpc/msgpack/preprocessor/logical/or.hpp \
        # rpc/msgpack/preprocessor/logical/xor.hpp \
        # rpc/msgpack/preprocessor/punctuation/comma.hpp \
        # rpc/msgpack/preprocessor/punctuation/comma_if.hpp \
        # rpc/msgpack/preprocessor/punctuation/is_begin_parens.hpp \
        # rpc/msgpack/preprocessor/punctuation/paren.hpp \
        # rpc/msgpack/preprocessor/punctuation/paren_if.hpp \
        # rpc/msgpack/preprocessor/punctuation/remove_parens.hpp \
        # rpc/msgpack/preprocessor/punctuation/detail/is_begin_parens.hpp \
        # rpc/msgpack/preprocessor/repetition/deduce_r.hpp \
        # rpc/msgpack/preprocessor/repetition/deduce_z.hpp \
        # rpc/msgpack/preprocessor/repetition/enum.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_binary_params.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_params.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_params_with_a_default.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_params_with_defaults.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_shifted.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_shifted_binary_params.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_shifted_params.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_trailing.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_trailing_binary_params.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_trailing_params.hpp \
        # rpc/msgpack/preprocessor/repetition/for.hpp \
        # rpc/msgpack/preprocessor/repetition/repeat.hpp \
        # rpc/msgpack/preprocessor/repetition/repeat_from_to.hpp \
        # rpc/msgpack/preprocessor/repetition/detail/for.hpp \
        # rpc/msgpack/preprocessor/repetition/detail/dmc/for.hpp \
        # rpc/msgpack/preprocessor/repetition/detail/edg/for.hpp \
        # rpc/msgpack/preprocessor/repetition/detail/msvc/for.hpp \
        # rpc/msgpack/preprocessor/selection/max.hpp \
        # rpc/msgpack/preprocessor/selection/min.hpp \
        # rpc/msgpack/preprocessor/seq/cat.hpp \
        # rpc/msgpack/preprocessor/seq/elem.hpp \
        # rpc/msgpack/preprocessor/seq/enum.hpp \
        # rpc/msgpack/preprocessor/seq/filter.hpp \
        # rpc/msgpack/preprocessor/seq/first_n.hpp \
        # rpc/msgpack/preprocessor/seq/fold_left.hpp \
        # rpc/msgpack/preprocessor/seq/fold_right.hpp \
        # rpc/msgpack/preprocessor/seq/for_each.hpp \
        # rpc/msgpack/preprocessor/seq/for_each_i.hpp \
        # rpc/msgpack/preprocessor/seq/for_each_product.hpp \
        # rpc/msgpack/preprocessor/seq/insert.hpp \
        # rpc/msgpack/preprocessor/seq/pop_back.hpp \
        # rpc/msgpack/preprocessor/seq/pop_front.hpp \
        # rpc/msgpack/preprocessor/seq/push_back.hpp \
        # rpc/msgpack/preprocessor/seq/push_front.hpp \
        # rpc/msgpack/preprocessor/seq/remove.hpp \
        # rpc/msgpack/preprocessor/seq/replace.hpp \
        # rpc/msgpack/preprocessor/seq/rest_n.hpp \
        # rpc/msgpack/preprocessor/seq/reverse.hpp \
        # rpc/msgpack/preprocessor/seq/seq.hpp \
        # rpc/msgpack/preprocessor/seq/size.hpp \
        # rpc/msgpack/preprocessor/seq/subseq.hpp \
        # rpc/msgpack/preprocessor/seq/to_array.hpp \
        # rpc/msgpack/preprocessor/seq/to_list.hpp \
        # rpc/msgpack/preprocessor/seq/to_tuple.hpp \
        # rpc/msgpack/preprocessor/seq/transform.hpp \
        # rpc/msgpack/preprocessor/seq/variadic_seq_to_seq.hpp \
        # rpc/msgpack/preprocessor/seq/detail/binary_transform.hpp \
        # rpc/msgpack/preprocessor/seq/detail/split.hpp \
        # rpc/msgpack/preprocessor/slot/counter.hpp \
        # rpc/msgpack/preprocessor/slot/slot.hpp \
        # rpc/msgpack/preprocessor/slot/detail/counter.hpp \
        # rpc/msgpack/preprocessor/slot/detail/def.hpp \
        # rpc/msgpack/preprocessor/slot/detail/shared.hpp \
        # rpc/msgpack/preprocessor/slot/detail/slot1.hpp \
        # rpc/msgpack/preprocessor/slot/detail/slot2.hpp \
        # rpc/msgpack/preprocessor/slot/detail/slot3.hpp \
        # rpc/msgpack/preprocessor/slot/detail/slot4.hpp \
        # rpc/msgpack/preprocessor/slot/detail/slot5.hpp \
        # rpc/msgpack/preprocessor/tuple/eat.hpp \
        # rpc/msgpack/preprocessor/tuple/elem.hpp \
        # rpc/msgpack/preprocessor/tuple/enum.hpp \
        # rpc/msgpack/preprocessor/tuple/insert.hpp \
        # rpc/msgpack/preprocessor/tuple/pop_back.hpp \
        # rpc/msgpack/preprocessor/tuple/pop_front.hpp \
        # rpc/msgpack/preprocessor/tuple/push_back.hpp \
        # rpc/msgpack/preprocessor/tuple/push_front.hpp \
        # rpc/msgpack/preprocessor/tuple/rem.hpp \
        # rpc/msgpack/preprocessor/tuple/remove.hpp \
        # rpc/msgpack/preprocessor/tuple/replace.hpp \
        # rpc/msgpack/preprocessor/tuple/reverse.hpp \
        # rpc/msgpack/preprocessor/tuple/size.hpp \
        # rpc/msgpack/preprocessor/tuple/to_array.hpp \
        # rpc/msgpack/preprocessor/tuple/to_list.hpp \
        # rpc/msgpack/preprocessor/tuple/to_seq.hpp \
        # rpc/msgpack/preprocessor/tuple/detail/is_single_return.hpp \
        # rpc/msgpack/preprocessor/variadic/elem.hpp \
        # rpc/msgpack/preprocessor/variadic/size.hpp \
        # rpc/msgpack/preprocessor/variadic/to_array.hpp \
        # rpc/msgpack/preprocessor/variadic/to_list.hpp \
        # rpc/msgpack/preprocessor/variadic/to_seq.hpp \
        # rpc/msgpack/preprocessor/variadic/to_tuple.hpp \
        # rpc/msgpack/preprocessor/variadic/detail/is_single_return.hpp \
        # rpc/nonstd/optional.hpp

trilearn_coach_SOURCES = ${SOURCES} \
        BasicCoach.cpp \
        BasicCoach.h \
        mainCoach.cpp #\
        # rpc/detail/all.h \
        # rpc/detail/any.h \
        # rpc/detail/async_writer.h \
        # rpc/detail/bool.h \
        # rpc/detail/call.h \
        # rpc/detail/client_error.h \
        # rpc/detail/constant.h \
        # rpc/detail/dev_utils.h \
        # rpc/detail/func_tools.h \
        # rpc/detail/func_traits.h \
        # rpc/detail/if.h \
        # rpc/detail/invoke.h \
        # rpc/detail/is_specialization_of.h \
        # rpc/detail/log.h \
        # rpc/detail/make_unique.h \
        # rpc/detail/not.h \
        # rpc/detail/pimpl.h \
        # rpc/detail/response.h \
        # rpc/detail/server_session.h \
        # rpc/detail/thread_group.h \
        # rpc/detail/util.h \
        # rpc/msgpack/cpp_config.hpp \
        # rpc/msgpack/fbuffer.h \
        # rpc/msgpack/fbuffer.hpp \
        # rpc/msgpack/gcc_atomic.h \
        # rpc/msgpack/iterator.hpp \
        # rpc/msgpack/meta.hpp \
        # rpc/msgpack/object.h \
        # rpc/msgpack/object.hpp \
        # rpc/msgpack/object_fwd.hpp \
        # rpc/msgpack/pack.h \
        # rpc/msgpack/pack.hpp \
        # rpc/msgpack/pack_define.h \
        # rpc/msgpack/pack_template.h \
        # rpc/msgpack/predef.h \
        # rpc/msgpack/preprocessor.hpp \
        # rpc/msgpack/sbuffer.h \
        # rpc/msgpack/sbuffer.hpp \
        # rpc/msgpack/sysdep.h \
        # rpc/msgpack/type.hpp \
        # rpc/msgpack/unpack.h \
        # rpc/msgpack/unpack.hpp \
        # rpc/msgpack/unpack_define.h \
        # rpc/msgpack/unpack_template.h \
        # rpc/msgpack/util.h \
        # rpc/msgpack/version.h \
        # rpc/msgpack/version.hpp \
        # rpc/msgpack/version_master.h \
        # rpc/msgpack/versioning.hpp \
        # rpc/msgpack/vrefbuffer.h \
        # rpc/msgpack/vrefbuffer.hpp \
        # rpc/msgpack/zbuffer.h \
        # rpc/msgpack/zbuffer.hpp \
        # rpc/msgpack/zone.h \
        # rpc/msgpack/zone.hpp \
        # rpc/msgpack/adaptor/adaptor_base.hpp \
        # rpc/msgpack/adaptor/array_ref.hpp \
        # rpc/msgpack/adaptor/bool.hpp \
        # rpc/msgpack/adaptor/char_ptr.hpp \
        # rpc/msgpack/adaptor/check_container_size.hpp \
        # rpc/msgpack/adaptor/define.hpp \
        # rpc/msgpack/adaptor/deque.hpp \
        # rpc/msgpack/adaptor/ext.hpp \
        # rpc/msgpack/adaptor/fixint.hpp \
        # rpc/msgpack/adaptor/float.hpp \
        # rpc/msgpack/adaptor/int.hpp \
        # rpc/msgpack/adaptor/list.hpp \
        # rpc/msgpack/adaptor/map.hpp \
        # rpc/msgpack/adaptor/msgpack_tuple.hpp \
        # rpc/msgpack/adaptor/nil.hpp \
        # rpc/msgpack/adaptor/pair.hpp \
        # rpc/msgpack/adaptor/raw.hpp \
        # rpc/msgpack/adaptor/set.hpp \
        # rpc/msgpack/adaptor/string.hpp \
        # rpc/msgpack/adaptor/v4raw.hpp \
        # rpc/msgpack/adaptor/vector.hpp \
        # rpc/msgpack/adaptor/vector_bool.hpp \
        # rpc/msgpack/adaptor/vector_char.hpp \
        # rpc/msgpack/adaptor/vector_unsigned_char.hpp \
        # rpc/msgpack/adaptor/boost/fusion.hpp \
        # rpc/msgpack/adaptor/boost/msgpack_variant.hpp \
        # rpc/msgpack/adaptor/boost/optional.hpp \
        # rpc/msgpack/adaptor/boost/string_ref.hpp \
        # rpc/msgpack/adaptor/cpp11/array.hpp \
        # rpc/msgpack/adaptor/cpp11/array_char.hpp \
        # rpc/msgpack/adaptor/cpp11/array_unsigned_char.hpp \
        # rpc/msgpack/adaptor/cpp11/forward_list.hpp \
        # rpc/msgpack/adaptor/cpp11/shared_ptr.hpp \
        # rpc/msgpack/adaptor/cpp11/tuple.hpp \
        # rpc/msgpack/adaptor/cpp11/unique_ptr.hpp \
        # rpc/msgpack/adaptor/cpp11/unordered_map.hpp \
        # rpc/msgpack/adaptor/cpp11/unordered_set.hpp \
        # rpc/msgpack/adaptor/detail/cpp03_define_array.hpp \
        # rpc/msgpack/adaptor/detail/cpp03_define_map.hpp \
        # rpc/msgpack/adaptor/detail/cpp03_msgpack_tuple.hpp \
        # rpc/msgpack/adaptor/detail/cpp11_define_array.hpp \
        # rpc/msgpack/adaptor/detail/cpp11_define_map.hpp \
        # rpc/msgpack/adaptor/detail/cpp11_msgpack_tuple.hpp \
        # rpc/msgpack/adaptor/tr1/unordered_map.hpp \
        # rpc/msgpack/adaptor/tr1/unordered_set.hpp \
        # rpc/msgpack/detail/cpp03_zone.hpp \
        # rpc/msgpack/detail/cpp11_zone.hpp \
        # rpc/msgpack/predef/architecture.h \
        # rpc/msgpack/predef/compiler.h \
        # rpc/msgpack/predef/language.h \
        # rpc/msgpack/predef/library.h \
        # rpc/msgpack/predef/make.h \
        # rpc/msgpack/predef/os.h \
        # rpc/msgpack/predef/other.h \
        # rpc/msgpack/predef/platform.h \
        # rpc/msgpack/predef/version.h \
        # rpc/msgpack/predef/version_number.h \
        # rpc/msgpack/predef/architecture/alpha.h \
        # rpc/msgpack/predef/architecture/arm.h \
        # rpc/msgpack/predef/architecture/blackfin.h \
        # rpc/msgpack/predef/architecture/convex.h \
        # rpc/msgpack/predef/architecture/ia64.h \
        # rpc/msgpack/predef/architecture/m68k.h \
        # rpc/msgpack/predef/architecture/mips.h \
        # rpc/msgpack/predef/architecture/parisc.h \
        # rpc/msgpack/predef/architecture/ppc.h \
        # rpc/msgpack/predef/architecture/pyramid.h \
        # rpc/msgpack/predef/architecture/rs6k.h \
        # rpc/msgpack/predef/architecture/sparc.h \
        # rpc/msgpack/predef/architecture/superh.h \
        # rpc/msgpack/predef/architecture/sys370.h \
        # rpc/msgpack/predef/architecture/sys390.h \
        # rpc/msgpack/predef/architecture/x86.h \
        # rpc/msgpack/predef/architecture/z.h \
        # rpc/msgpack/predef/architecture/x86/32.h \
        # rpc/msgpack/predef/architecture/x86/64.h \
        # rpc/msgpack/predef/compiler/borland.h \
        # rpc/msgpack/predef/compiler/clang.h \
        # rpc/msgpack/predef/compiler/comeau.h \
        # rpc/msgpack/predef/compiler/compaq.h \
        # rpc/msgpack/predef/compiler/diab.h \
        # rpc/msgpack/predef/compiler/digitalmars.h \
        # rpc/msgpack/predef/compiler/dignus.h \
        # rpc/msgpack/predef/compiler/edg.h \
        # rpc/msgpack/predef/compiler/ekopath.h \
        # rpc/msgpack/predef/compiler/gcc.h \
        # rpc/msgpack/predef/compiler/gcc_xml.h \
        # rpc/msgpack/predef/compiler/greenhills.h \
        # rpc/msgpack/predef/compiler/hp_acc.h \
        # rpc/msgpack/predef/compiler/iar.h \
        # rpc/msgpack/predef/compiler/ibm.h \
        # rpc/msgpack/predef/compiler/intel.h \
        # rpc/msgpack/predef/compiler/kai.h \
        # rpc/msgpack/predef/compiler/llvm.h \
        # rpc/msgpack/predef/compiler/metaware.h \
        # rpc/msgpack/predef/compiler/metrowerks.h \
        # rpc/msgpack/predef/compiler/microtec.h \
        # rpc/msgpack/predef/compiler/mpw.h \
        # rpc/msgpack/predef/compiler/palm.h \
        # rpc/msgpack/predef/compiler/pgi.h \
        # rpc/msgpack/predef/compiler/sgi_mipspro.h \
        # rpc/msgpack/predef/compiler/sunpro.h \
        # rpc/msgpack/predef/compiler/tendra.h \
        # rpc/msgpack/predef/compiler/visualc.h \
        # rpc/msgpack/predef/compiler/watcom.h \
        # rpc/msgpack/predef/detail/_cassert.h \
        # rpc/msgpack/predef/detail/_exception.h \
        # rpc/msgpack/predef/detail/comp_detected.h \
        # rpc/msgpack/predef/detail/endian_compat.h \
        # rpc/msgpack/predef/detail/os_detected.h \
        # rpc/msgpack/predef/detail/platform_detected.h \
        # rpc/msgpack/predef/detail/test.h \
        # rpc/msgpack/predef/language/objc.h \
        # rpc/msgpack/predef/language/stdc.h \
        # rpc/msgpack/predef/language/stdcpp.h \
        # rpc/msgpack/predef/library/c.h \
        # rpc/msgpack/predef/library/std.h \
        # rpc/msgpack/predef/library/c/_prefix.h \
        # rpc/msgpack/predef/library/c/gnu.h \
        # rpc/msgpack/predef/library/c/uc.h \
        # rpc/msgpack/predef/library/c/vms.h \
        # rpc/msgpack/predef/library/c/zos.h \
        # rpc/msgpack/predef/library/std/_prefix.h \
        # rpc/msgpack/predef/library/std/cxx.h \
        # rpc/msgpack/predef/library/std/dinkumware.h \
        # rpc/msgpack/predef/library/std/libcomo.h \
        # rpc/msgpack/predef/library/std/modena.h \
        # rpc/msgpack/predef/library/std/msl.h \
        # rpc/msgpack/predef/library/std/roguewave.h \
        # rpc/msgpack/predef/library/std/sgi.h \
        # rpc/msgpack/predef/library/std/stdcpp3.h \
        # rpc/msgpack/predef/library/std/stlport.h \
        # rpc/msgpack/predef/library/std/vacpp.h \
        # rpc/msgpack/predef/os/aix.h \
        # rpc/msgpack/predef/os/amigaos.h \
        # rpc/msgpack/predef/os/android.h \
        # rpc/msgpack/predef/os/beos.h \
        # rpc/msgpack/predef/os/bsd.h \
        # rpc/msgpack/predef/os/cygwin.h \
        # rpc/msgpack/predef/os/haiku.h \
        # rpc/msgpack/predef/os/hpux.h \
        # rpc/msgpack/predef/os/ios.h \
        # rpc/msgpack/predef/os/irix.h \
        # rpc/msgpack/predef/os/linux.h \
        # rpc/msgpack/predef/os/macos.h \
        # rpc/msgpack/predef/os/os400.h \
        # rpc/msgpack/predef/os/qnxnto.h \
        # rpc/msgpack/predef/os/solaris.h \
        # rpc/msgpack/predef/os/unix.h \
        # rpc/msgpack/predef/os/vms.h \
        # rpc/msgpack/predef/os/windows.h \
        # rpc/msgpack/predef/os/bsd/bsdi.h \
        # rpc/msgpack/predef/os/bsd/dragonfly.h \
        # rpc/msgpack/predef/os/bsd/free.h \
        # rpc/msgpack/predef/os/bsd/net.h \
        # rpc/msgpack/predef/os/bsd/open.h \
        # rpc/msgpack/predef/other/endian.h \
        # rpc/msgpack/predef/platform/mingw.h \
        # rpc/msgpack/predef/platform/windows_desktop.h \
        # rpc/msgpack/predef/platform/windows_phone.h \
        # rpc/msgpack/predef/platform/windows_runtime.h \
        # rpc/msgpack/predef/platform/windows_store.h \
        # rpc/msgpack/preprocessor/arithmetic.hpp \
        # rpc/msgpack/preprocessor/array.hpp \
        # rpc/msgpack/preprocessor/assert_msg.hpp \
        # rpc/msgpack/preprocessor/cat.hpp \
        # rpc/msgpack/preprocessor/comma.hpp \
        # rpc/msgpack/preprocessor/comma_if.hpp \
        # rpc/msgpack/preprocessor/comparison.hpp \
        # rpc/msgpack/preprocessor/control.hpp \
        # rpc/msgpack/preprocessor/debug.hpp \
        # rpc/msgpack/preprocessor/dec.hpp \
        # rpc/msgpack/preprocessor/empty.hpp \
        # rpc/msgpack/preprocessor/enum.hpp \
        # rpc/msgpack/preprocessor/enum_params.hpp \
        # rpc/msgpack/preprocessor/enum_params_with_a_default.hpp \
        # rpc/msgpack/preprocessor/enum_params_with_defaults.hpp \
        # rpc/msgpack/preprocessor/enum_shifted.hpp \
        # rpc/msgpack/preprocessor/enum_shifted_params.hpp \
        # rpc/msgpack/preprocessor/expand.hpp \
        # rpc/msgpack/preprocessor/expr_if.hpp \
        # rpc/msgpack/preprocessor/facilities.hpp \
        # rpc/msgpack/preprocessor/for.hpp \
        # rpc/msgpack/preprocessor/identity.hpp \
        # rpc/msgpack/preprocessor/if.hpp \
        # rpc/msgpack/preprocessor/inc.hpp \
        # rpc/msgpack/preprocessor/iterate.hpp \
        # rpc/msgpack/preprocessor/iteration.hpp \
        # rpc/msgpack/preprocessor/library.hpp \
        # rpc/msgpack/preprocessor/limits.hpp \
        # rpc/msgpack/preprocessor/list.hpp \
        # rpc/msgpack/preprocessor/logical.hpp \
        # rpc/msgpack/preprocessor/max.hpp \
        # rpc/msgpack/preprocessor/min.hpp \
        # rpc/msgpack/preprocessor/punctuation.hpp \
        # rpc/msgpack/preprocessor/repeat.hpp \
        # rpc/msgpack/preprocessor/repeat_2nd.hpp \
        # rpc/msgpack/preprocessor/repeat_3rd.hpp \
        # rpc/msgpack/preprocessor/repeat_from_to.hpp \
        # rpc/msgpack/preprocessor/repeat_from_to_2nd.hpp \
        # rpc/msgpack/preprocessor/repeat_from_to_3rd.hpp \
        # rpc/msgpack/preprocessor/repetition.hpp \
        # rpc/msgpack/preprocessor/selection.hpp \
        # rpc/msgpack/preprocessor/seq.hpp \
        # rpc/msgpack/preprocessor/slot.hpp \
        # rpc/msgpack/preprocessor/stringize.hpp \
        # rpc/msgpack/preprocessor/tuple.hpp \
        # rpc/msgpack/preprocessor/variadic.hpp \
        # rpc/msgpack/preprocessor/while.hpp \
        # rpc/msgpack/preprocessor/wstringize.hpp \
        # rpc/msgpack/preprocessor/arithmetic/add.hpp \
        # rpc/msgpack/preprocessor/arithmetic/dec.hpp \
        # rpc/msgpack/preprocessor/arithmetic/div.hpp \
        # rpc/msgpack/preprocessor/arithmetic/inc.hpp \
        # rpc/msgpack/preprocessor/arithmetic/mod.hpp \
        # rpc/msgpack/preprocessor/arithmetic/mul.hpp \
        # rpc/msgpack/preprocessor/arithmetic/sub.hpp \
        # rpc/msgpack/preprocessor/arithmetic/detail/div_base.hpp \
        # rpc/msgpack/preprocessor/array/data.hpp \
        # rpc/msgpack/preprocessor/array/elem.hpp \
        # rpc/msgpack/preprocessor/array/enum.hpp \
        # rpc/msgpack/preprocessor/array/insert.hpp \
        # rpc/msgpack/preprocessor/array/pop_back.hpp \
        # rpc/msgpack/preprocessor/array/pop_front.hpp \
        # rpc/msgpack/preprocessor/array/push_back.hpp \
        # rpc/msgpack/preprocessor/array/push_front.hpp \
        # rpc/msgpack/preprocessor/array/remove.hpp \
        # rpc/msgpack/preprocessor/array/replace.hpp \
        # rpc/msgpack/preprocessor/array/reverse.hpp \
        # rpc/msgpack/preprocessor/array/size.hpp \
        # rpc/msgpack/preprocessor/array/to_list.hpp \
        # rpc/msgpack/preprocessor/array/to_seq.hpp \
        # rpc/msgpack/preprocessor/array/to_tuple.hpp \
        # rpc/msgpack/preprocessor/array/detail/get_data.hpp \
        # rpc/msgpack/preprocessor/comparison/equal.hpp \
        # rpc/msgpack/preprocessor/comparison/greater.hpp \
        # rpc/msgpack/preprocessor/comparison/greater_equal.hpp \
        # rpc/msgpack/preprocessor/comparison/less.hpp \
        # rpc/msgpack/preprocessor/comparison/less_equal.hpp \
        # rpc/msgpack/preprocessor/comparison/not_equal.hpp \
        # rpc/msgpack/preprocessor/config/config.hpp \
        # rpc/msgpack/preprocessor/config/limits.hpp \
        # rpc/msgpack/preprocessor/control/deduce_d.hpp \
        # rpc/msgpack/preprocessor/control/expr_if.hpp \
        # rpc/msgpack/preprocessor/control/expr_iif.hpp \
        # rpc/msgpack/preprocessor/control/if.hpp \
        # rpc/msgpack/preprocessor/control/iif.hpp \
        # rpc/msgpack/preprocessor/control/while.hpp \
        # rpc/msgpack/preprocessor/control/detail/while.hpp \
        # rpc/msgpack/preprocessor/control/detail/dmc/while.hpp \
        # rpc/msgpack/preprocessor/control/detail/edg/while.hpp \
        # rpc/msgpack/preprocessor/control/detail/msvc/while.hpp \
        # rpc/msgpack/preprocessor/debug/assert.hpp \
        # rpc/msgpack/preprocessor/debug/error.hpp \
        # rpc/msgpack/preprocessor/debug/line.hpp \
        # rpc/msgpack/preprocessor/detail/auto_rec.hpp \
        # rpc/msgpack/preprocessor/detail/check.hpp \
        # rpc/msgpack/preprocessor/detail/is_binary.hpp \
        # rpc/msgpack/preprocessor/detail/is_nullary.hpp \
        # rpc/msgpack/preprocessor/detail/is_unary.hpp \
        # rpc/msgpack/preprocessor/detail/null.hpp \
        # rpc/msgpack/preprocessor/detail/split.hpp \
        # rpc/msgpack/preprocessor/detail/dmc/auto_rec.hpp \
        # rpc/msgpack/preprocessor/facilities/apply.hpp \
        # rpc/msgpack/preprocessor/facilities/empty.hpp \
        # rpc/msgpack/preprocessor/facilities/expand.hpp \
        # rpc/msgpack/preprocessor/facilities/identity.hpp \
        # rpc/msgpack/preprocessor/facilities/intercept.hpp \
        # rpc/msgpack/preprocessor/facilities/is_1.hpp \
        # rpc/msgpack/preprocessor/facilities/is_empty.hpp \
        # rpc/msgpack/preprocessor/facilities/is_empty_or_1.hpp \
        # rpc/msgpack/preprocessor/facilities/is_empty_variadic.hpp \
        # rpc/msgpack/preprocessor/facilities/overload.hpp \
        # rpc/msgpack/preprocessor/facilities/detail/is_empty.hpp \
        # rpc/msgpack/preprocessor/iteration/iterate.hpp \
        # rpc/msgpack/preprocessor/iteration/local.hpp \
        # rpc/msgpack/preprocessor/iteration/self.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/finish.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/local.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/rlocal.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/self.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/start.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/lower1.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/lower2.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/lower3.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/lower4.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/lower5.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/upper1.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/upper2.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/upper3.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/upper4.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/bounds/upper5.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/forward1.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/forward2.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/forward3.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/forward4.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/forward5.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/reverse1.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/reverse2.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/reverse3.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/reverse4.hpp \
        # rpc/msgpack/preprocessor/iteration/detail/iter/reverse5.hpp \
        # rpc/msgpack/preprocessor/list/adt.hpp \
        # rpc/msgpack/preprocessor/list/append.hpp \
        # rpc/msgpack/preprocessor/list/at.hpp \
        # rpc/msgpack/preprocessor/list/cat.hpp \
        # rpc/msgpack/preprocessor/list/enum.hpp \
        # rpc/msgpack/preprocessor/list/filter.hpp \
        # rpc/msgpack/preprocessor/list/first_n.hpp \
        # rpc/msgpack/preprocessor/list/fold_left.hpp \
        # rpc/msgpack/preprocessor/list/fold_right.hpp \
        # rpc/msgpack/preprocessor/list/for_each.hpp \
        # rpc/msgpack/preprocessor/list/for_each_i.hpp \
        # rpc/msgpack/preprocessor/list/for_each_product.hpp \
        # rpc/msgpack/preprocessor/list/rest_n.hpp \
        # rpc/msgpack/preprocessor/list/reverse.hpp \
        # rpc/msgpack/preprocessor/list/size.hpp \
        # rpc/msgpack/preprocessor/list/to_array.hpp \
        # rpc/msgpack/preprocessor/list/to_seq.hpp \
        # rpc/msgpack/preprocessor/list/to_tuple.hpp \
        # rpc/msgpack/preprocessor/list/transform.hpp \
        # rpc/msgpack/preprocessor/list/detail/fold_left.hpp \
        # rpc/msgpack/preprocessor/list/detail/fold_right.hpp \
        # rpc/msgpack/preprocessor/list/detail/dmc/fold_left.hpp \
        # rpc/msgpack/preprocessor/list/detail/edg/fold_left.hpp \
        # rpc/msgpack/preprocessor/list/detail/edg/fold_right.hpp \
        # rpc/msgpack/preprocessor/logical/and.hpp \
        # rpc/msgpack/preprocessor/logical/bitand.hpp \
        # rpc/msgpack/preprocessor/logical/bitnor.hpp \
        # rpc/msgpack/preprocessor/logical/bitor.hpp \
        # rpc/msgpack/preprocessor/logical/bitxor.hpp \
        # rpc/msgpack/preprocessor/logical/bool.hpp \
        # rpc/msgpack/preprocessor/logical/compl.hpp \
        # rpc/msgpack/preprocessor/logical/nor.hpp \
        # rpc/msgpack/preprocessor/logical/not.hpp \
        # rpc/msgpack/preprocessor/logical/or.hpp \
        # rpc/msgpack/preprocessor/logical/xor.hpp \
        # rpc/msgpack/preprocessor/punctuation/comma.hpp \
        # rpc/msgpack/preprocessor/punctuation/comma_if.hpp \
        # rpc/msgpack/preprocessor/punctuation/is_begin_parens.hpp \
        # rpc/msgpack/preprocessor/punctuation/paren.hpp \
        # rpc/msgpack/preprocessor/punctuation/paren_if.hpp \
        # rpc/msgpack/preprocessor/punctuation/remove_parens.hpp \
        # rpc/msgpack/preprocessor/punctuation/detail/is_begin_parens.hpp \
        # rpc/msgpack/preprocessor/repetition/deduce_r.hpp \
        # rpc/msgpack/preprocessor/repetition/deduce_z.hpp \
        # rpc/msgpack/preprocessor/repetition/enum.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_binary_params.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_params.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_params_with_a_default.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_params_with_defaults.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_shifted.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_shifted_binary_params.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_shifted_params.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_trailing.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_trailing_binary_params.hpp \
        # rpc/msgpack/preprocessor/repetition/enum_trailing_params.hpp \
        # rpc/msgpack/preprocessor/repetition/for.hpp \
        # rpc/msgpack/preprocessor/repetition/repeat.hpp \
        # rpc/msgpack/preprocessor/repetition/repeat_from_to.hpp \
        # rpc/msgpack/preprocessor/repetition/detail/for.hpp \
        # rpc/msgpack/preprocessor/repetition/detail/dmc/for.hpp \
        # rpc/msgpack/preprocessor/repetition/detail/edg/for.hpp \
        # rpc/msgpack/preprocessor/repetition/detail/msvc/for.hpp \
        # rpc/msgpack/preprocessor/selection/max.hpp \
        # rpc/msgpack/preprocessor/selection/min.hpp \
        # rpc/msgpack/preprocessor/seq/cat.hpp \
        # rpc/msgpack/preprocessor/seq/elem.hpp \
        # rpc/msgpack/preprocessor/seq/enum.hpp \
        # rpc/msgpack/preprocessor/seq/filter.hpp \
        # rpc/msgpack/preprocessor/seq/first_n.hpp \
        # rpc/msgpack/preprocessor/seq/fold_left.hpp \
        # rpc/msgpack/preprocessor/seq/fold_right.hpp \
        # rpc/msgpack/preprocessor/seq/for_each.hpp \
        # rpc/msgpack/preprocessor/seq/for_each_i.hpp \
        # rpc/msgpack/preprocessor/seq/for_each_product.hpp \
        # rpc/msgpack/preprocessor/seq/insert.hpp \
        # rpc/msgpack/preprocessor/seq/pop_back.hpp \
        # rpc/msgpack/preprocessor/seq/pop_front.hpp \
        # rpc/msgpack/preprocessor/seq/push_back.hpp \
        # rpc/msgpack/preprocessor/seq/push_front.hpp \
        # rpc/msgpack/preprocessor/seq/remove.hpp \
        # rpc/msgpack/preprocessor/seq/replace.hpp \
        # rpc/msgpack/preprocessor/seq/rest_n.hpp \
        # rpc/msgpack/preprocessor/seq/reverse.hpp \
        # rpc/msgpack/preprocessor/seq/seq.hpp \
        # rpc/msgpack/preprocessor/seq/size.hpp \
        # rpc/msgpack/preprocessor/seq/subseq.hpp \
        # rpc/msgpack/preprocessor/seq/to_array.hpp \
        # rpc/msgpack/preprocessor/seq/to_list.hpp \
        # rpc/msgpack/preprocessor/seq/to_tuple.hpp \
        # rpc/msgpack/preprocessor/seq/transform.hpp \
        # rpc/msgpack/preprocessor/seq/variadic_seq_to_seq.hpp \
        # rpc/msgpack/preprocessor/seq/detail/binary_transform.hpp \
        # rpc/msgpack/preprocessor/seq/detail/split.hpp \
        # rpc/msgpack/preprocessor/slot/counter.hpp \
        # rpc/msgpack/preprocessor/slot/slot.hpp \
        # rpc/msgpack/preprocessor/slot/detail/counter.hpp \
        # rpc/msgpack/preprocessor/slot/detail/def.hpp \
        # rpc/msgpack/preprocessor/slot/detail/shared.hpp \
        # rpc/msgpack/preprocessor/slot/detail/slot1.hpp \
        # rpc/msgpack/preprocessor/slot/detail/slot2.hpp \
        # rpc/msgpack/preprocessor/slot/detail/slot3.hpp \
        # rpc/msgpack/preprocessor/slot/detail/slot4.hpp \
        # rpc/msgpack/preprocessor/slot/detail/slot5.hpp \
        # rpc/msgpack/preprocessor/tuple/eat.hpp \
        # rpc/msgpack/preprocessor/tuple/elem.hpp \
        # rpc/msgpack/preprocessor/tuple/enum.hpp \
        # rpc/msgpack/preprocessor/tuple/insert.hpp \
        # rpc/msgpack/preprocessor/tuple/pop_back.hpp \
        # rpc/msgpack/preprocessor/tuple/pop_front.hpp \
        # rpc/msgpack/preprocessor/tuple/push_back.hpp \
        # rpc/msgpack/preprocessor/tuple/push_front.hpp \
        # rpc/msgpack/preprocessor/tuple/rem.hpp \
        # rpc/msgpack/preprocessor/tuple/remove.hpp \
        # rpc/msgpack/preprocessor/tuple/replace.hpp \
        # rpc/msgpack/preprocessor/tuple/reverse.hpp \
        # rpc/msgpack/preprocessor/tuple/size.hpp \
        # rpc/msgpack/preprocessor/tuple/to_array.hpp \
        # rpc/msgpack/preprocessor/tuple/to_list.hpp \
        # rpc/msgpack/preprocessor/tuple/to_seq.hpp \
        # rpc/msgpack/preprocessor/tuple/detail/is_single_return.hpp \
        # rpc/msgpack/preprocessor/variadic/elem.hpp \
        # rpc/msgpack/preprocessor/variadic/size.hpp \
        # rpc/msgpack/preprocessor/variadic/to_array.hpp \
        # rpc/msgpack/preprocessor/variadic/to_list.hpp \
        # rpc/msgpack/preprocessor/variadic/to_seq.hpp \
        # rpc/msgpack/preprocessor/variadic/to_tuple.hpp \
        # rpc/msgpack/preprocessor/variadic/detail/is_single_return.hpp \
        # rpc/nonstd/optional.hpp

## also distribute configuration file with distribution
EXTRA_DIST = formations.conf player.conf

