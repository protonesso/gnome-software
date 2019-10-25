/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2019 Jonathan Kang <jonathankang@gnome.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define GS_TYPE_EULA_DIALOG (gs_eula_dialog_get_type ())
G_DECLARE_FINAL_TYPE (GsEulaDialog, gs_eula_dialog, GS, EULA_DIALOG, GtkDialog)

void gs_eula_dialog_populate_license_agreement (GsEulaDialog *dialog,
                                                const gchar *license_agreement);
GsEulaDialog *gs_eula_dialog_new (void);

G_END_DECLS
