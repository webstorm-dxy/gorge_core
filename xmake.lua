add_rules("mode.debug", "mode.release")
add_requires("boost")
add_rules("plugin.vsxmake.autoupdate")
add_rules("plugin.compile_commands.autoupdate", {outputdir = "./"})
set_languages("c++23")

target("gorge_core_cpp")
    set_kind("shared")
    -- set_toolchains("clang")
    
    add_packages("boost")
    add_headerfiles("src/objective/**.h","src/**.h")
    add_files("src/lib.cpp","src/objective/*.cpp")
    -- 如果是 Windows，添加 DLL 导出定义
    if is_plat("windows") then
        add_defines("GORGE_CORE_CPP_EXPORTS")
    end
        
    -- 确保所有符号都可见（对 Linux/macOS 也有用）
    if is_plat("linux", "macosx") then
        add_cxflags("-fvisibility=default")
    end

target("gorge_core")
    set_kind("binary")
    -- set_toolchains("clang")
    add_deps("gorge_core_cpp")
    
    
    add_files("src/main.cpp")
    
    add_linkdirs("$(buildir)/$(plat)/$(arch)/$(mode)")
    add_links("gorge_core_cpp")
--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--
