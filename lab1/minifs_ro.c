/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPLv2.
  See the file COPYING.
*/

/** @file
 *
 * minimal example filesystem using high-level API
 *
 * Compile with:
 *
 *     gcc -Wall hello.c `pkg-config fuse3 --cflags --libs` -o hello
 *
 * ## Source code ##
 * \include hello.c
 */


#define FUSE_USE_VERSION 31

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <assert.h>

/*
 * Command line options
 *
 * We can't set default values for the char* fields here because
 * fuse_opt_parse would attempt to free() them when the user specifies
 * different values on the command line.
 */
static struct minifs_file {
	const char *path;
	const char *name;
	const char *data;
} options, options2;

#define OPTION(t, p)                           \
    { t, offsetof(struct minifs_file, p), 1 }
static const struct fuse_opt option_spec[] = {
	OPTION("--name=%s", name),
	OPTION("--contents=%s", data),
	FUSE_OPT_END
};

static void *minifs_init(struct fuse_conn_info *conn,
			struct fuse_config *cfg)
{
	(void) conn;
	cfg->kernel_cache = 1;
	return NULL;
}

static int minifs_getattr(const char *path, struct stat *stbuf,
			 struct fuse_file_info *fi)
{
	(void) fi;
	int res = 0;

	memset(stbuf, 0, sizeof(struct stat));
	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = S_IFDIR | 0555;
		stbuf->st_nlink = 2;
	} else if (strcmp(path+1, options.name) == 0) {
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(options.data);
	} else if (strcmp(path+1, options2.name) == 0) {
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(options2.data);
	}else
		res = -ENOENT;

	return res;
}

static int minifs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			 off_t offset, struct fuse_file_info *fi,
			 enum fuse_readdir_flags flags)
{
	(void) offset;
	(void) fi;
	(void) flags;

	if (strcmp(path, "/") != 0)
		return -ENOENT;

	filler(buf, ".", NULL, 0, 0);
	filler(buf, "..", NULL, 0, 0);
	filler(buf, options.name, NULL, 0, 0);
	filler(buf, options2.name, NULL, 0, 0);

	return 0;
}

static int minifs_open(const char *path, struct fuse_file_info *fi)
{
	if ((strcmp(path+1, options.name) != 0) && (strcmp(path+1, options2.name) != 0))
		return -ENOENT;

	if ((fi->flags & O_ACCMODE) != O_RDONLY)
		return -EACCES;

	return 0;
}

static int minifs_read(const char *path, char *buf, size_t size, off_t offset,
		      struct fuse_file_info *fi)
{
	size_t len;
	(void) fi;

	const char *content = NULL;
	if(strcmp(path+1, options.name) == 0)
		content = options.data;
	if(strcmp(path+1, options2.name) == 0)
		content = options2.data;
	if(content == NULL)
		return -ENOENT;

	len = strlen(content);
	if (offset < len) {
		if (offset + size > len)
			size = len - offset;
		memcpy(buf, content + offset, size);
	} else
		size = 0;

	return size;
}

static const struct fuse_operations hello_oper = {
	.init           = minifs_init,
	.getattr	= minifs_getattr,
	.readdir	= minifs_readdir,
	.open		= minifs_open,
	.read		= minifs_read,
};

static void show_help(const char *progname)
{
	printf("usage: %s [options] <mountpoint>\n\n", progname);
	printf("File-system specific options:\n"
	       "    --name=<s>          Name of the \"hello\" file\n"
	       "                        (default: \"hello\")\n"
	       "    --contents=<s>      Contents \"hello\" file\n"
	       "                        (default \"Hello, World!\\n\")\n"
	       "\n");
}

int main(int argc, char *argv[])
{
	int ret;
	struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

	/* Set defaults -- we have to use strdup so that
	   fuse_opt_parse can free the defaults if other
	   values are specified */
	options.name = strdup("hello.txt");
	options.data = strdup("Hello World!\n");
	options.path = strdup("/hello.txt");
	options2.name = strdup("about.txt");
	options2.data = strdup("This filesystem has implemented the getattr (similar to stat), readdir, open, and read \n"
				"syscalls. It is read-only. feel free to fool around!\n");
	options2.path = strdup("/about.txt");

	/* Parse options */
//	if (fuse_opt_parse(&args, &options, option_spec, NULL) == -1)
//		return 1;

	/* When --help is specified, first print our own file-system
	   specific help text, then signal fuse_main to show
	   additional help (by adding `--help` to the options again)
	   without usage: line (by setting argv[0] to the empty
	   string) */
//	if (options.show_help) {
//		show_help(argv[0]);
//		assert(fuse_opt_add_arg(&args, "--help") == 0);
//		args.argv[0][0] = '\0';
//	}

	ret = fuse_main(args.argc, args.argv, &hello_oper, NULL);
	fuse_opt_free_args(&args);
	return ret;
}
