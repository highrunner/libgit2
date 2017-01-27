/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */
#ifndef INCLUDE_oidmap_h__
#define INCLUDE_oidmap_h__

#include "common.h"
#include "git2/oid.h"

#define kmalloc git__malloc
#define kcalloc git__calloc
#define krealloc git__realloc
#define kreallocarray git__reallocarray
#define kfree git__free
#include "khash.h"

__KHASH_TYPE(oid, const git_oid *, void *)
typedef khash_t(oid) git_oidmap;

GIT_INLINE(khint_t) git_oidmap_hash(const git_oid *oid)
{
	khint_t h;
	memcpy(&h, oid, sizeof(khint_t));
	return h;
}

#define GIT__USE_OIDMAP \
	__KHASH_IMPL(oid, static kh_inline, const git_oid *, void *, 1, git_oidmap_hash, git_oid_equal)

git_oidmap *git_oidmap_alloc(void);
#define git_oidmap_free(h) git_oidmap__free(h); (h) = NULL
void git_oidmap__free(git_oidmap *map);
void git_oidmap_clear(git_oidmap *map);

size_t git_oidmap_size(git_oidmap *map);

size_t git_oidmap_lookup_index(git_oidmap *map, const git_oid *key);
int git_oidmap_valid_index(git_oidmap *map, size_t idx);

int git_oidmap_exists(git_oidmap *map, const git_oid *key);
int git_oidmap_has_data(git_oidmap *map, size_t idx);

const git_oid *git_oidmap_key(git_oidmap *map, size_t idx);
void git_oidmap_set_key_at(git_oidmap *map, size_t idx, git_oid *key);
void *git_oidmap_value_at(git_oidmap *map, size_t idx);
void git_oidmap_set_value_at(git_oidmap *map, size_t idx, void *value);
void git_oidmap_delete_at(git_oidmap *map, size_t idx);

int git_oidmap_put(git_oidmap *map, const git_oid *key, int *err);
void git_oidmap_insert(git_oidmap *map, const git_oid *key, void *value, int *rval);
void git_oidmap_delete(git_oidmap *map, const git_oid *key);

#define git_oidmap_foreach_value kh_foreach_value

#define git_oidmap_begin	kh_begin
#define git_oidmap_end		kh_end

#endif
