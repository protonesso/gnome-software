/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2019 Jonathan Kang <jonathankang@gnome.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

#pragma once

#include <glib-object.h>
#include <packagekit-glib2/packagekit.h>

G_BEGIN_DECLS

#define GS_TYPE_TASK (gs_task_get_type ())
G_DECLARE_FINAL_TYPE (GsTask, gs_task, GS, TASK, PkTask)

const gchar *gs_task_get_package_id (GsTask *task);
const gchar *gs_task_get_vendor_name (GsTask *task);
const gchar *gs_task_get_license_agreement (GsTask *task);
GsTask *gs_task_new (void);

G_END_DECLS
