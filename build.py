from conan.packager import ConanMultiPackager
from conans.tools import os_info
import platform

if __name__ == "__main__":
    builder = ConanMultiPackager(args="--build missing")
    builder.add_common_builds(shared_option_name="simple:shared", pure_c=True)
    builder.builds = [
        [settings, options, env_vars, build_requires]
        for settings, options, env_vars, build_requires in builder.builds
        if (not (os_info.is_linux and settings["arch"] == "x86")) and options['simple:shared'] == True 
    ]
    builder.run()
