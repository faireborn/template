const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const mode = b.standardOptimizeOption(.{});

    const build_mod = b.addModule("build", .{
        .target = target,
        .optimize = mode,
        .link_libc = true,
    });

    const common_prefix_search_mod = b.addModule("common_prefix_search", .{
        .target = target,
        .optimize = mode,
        .link_libc = true,
    });

    build_mod.addCSourceFile(.{
        .file = b.path("src/build.cc"),
        .flags = &[_][]const u8{"-std=c++17"},
    });

    common_prefix_search_mod.addCSourceFile(.{
        .file = b.path("src/common_prefix_search.cc"),
        .flags = &[_][]const u8{"-std=c++17"},
    });

    const build_exe = b.addExecutable(.{
        .name = "build",
        .root_module = build_mod,
    });
    build_exe.installHeadersDirectory(b.path("third_party"), "", .{
        .include_extensions = &.{"h"},
    });
    build_exe.linkLibCpp();
    b.installArtifact(build_exe);

    const common_prefix_search_exe = b.addExecutable(.{
        .name = "common_prefix_search",
        .root_module = common_prefix_search_mod,
    });
    common_prefix_search_exe.linkLibCpp();
    b.installArtifact(common_prefix_search_exe);

    const run_build = b.addRunArtifact(build_exe);
    run_build.step.dependOn(b.getInstallStep());

    const run_common_prefix_search = b.addRunArtifact(common_prefix_search_exe);
    run_build.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_build.addArgs(args);
        run_common_prefix_search.addArgs(args);
    }

    const build_step = b.step("build", "Run the app");
    build_step.dependOn(&run_build.step);

    const common_prefix_search_step = b.step("common_prefix_search", "Common prefix search");
    common_prefix_search_step.dependOn(&run_common_prefix_search.step);
}
