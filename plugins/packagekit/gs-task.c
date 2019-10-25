/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2019 Jonathan Kang <jonathankang@gnome.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

#include <packagekit-glib2/packagekit.h>

#include "gs-task.h"

enum
{
	EULA_QUESTION,
	LAST_SIGNAL
};

struct _GsTask
{
	/*< private >*/
	PkTask parent_instance;

	gchar *package_id;
	gchar *vendor_name;
	gchar *license_agreement;
	guint request;
};

struct _GsTaskClass
{
	PkTaskClass parent_class;
};

G_DEFINE_TYPE (GsTask, gs_task, PK_TYPE_TASK)

	static guint signals[LAST_SIGNAL] = { 0 };

const gchar *
gs_task_get_package_id (GsTask *self)
{
	g_return_val_if_fail (GS_IS_TASK (self), NULL);

	return self->package_id;
}

const gchar *
gs_task_get_vendor_name (GsTask *self)
{
	g_return_val_if_fail (GS_IS_TASK (self), NULL);

	return self->vendor_name;
}

const gchar *
gs_task_get_license_agreement (GsTask *self)
{
	g_return_val_if_fail (GS_IS_TASK (self), NULL);

	return self->license_agreement;
}

static void
gs_task_untrusted_question (PkTask *task,
			    guint request,
			    PkResults *results)
{}

static void
gs_task_key_question (PkTask *task,
		      guint request,
		      PkResults *results)
{
	g_warning ("key question\n");
}

static void
gs_task_media_change_question (PkTask *task,
			       guint request,
			       PkResults *results)
{
	g_warning ("media change question\n");
}

static void
gs_task_eula_question (PkTask *task,
                       guint request,
                       PkResults *results)
{
	PkEulaRequired *item;
	g_autoptr(GPtrArray) array = NULL;
	GsTask *self;

	g_warning ("eula question\n");

	self = GS_TASK (task);

	/* Save the current request. */
	self->request = request;

	array = pk_results_get_eula_required_array (results);
	if (array->len != 1)
	{
		g_warning ("array length %u, aborting", array->len);
	}

	item = g_ptr_array_index (array, 0);
	g_object_get (item,
		      "package-id", &self->package_id,
		      "vendor-name", &self->vendor_name,
		      "license-agreement", &self->license_agreement,
		      NULL);

	/* Show the eula window here. Emit a signal? */
	g_signal_emit (GS_TASK (task), signals[EULA_QUESTION], 0, item);
}

static void
gs_task_finalize (GObject *object)
{
	GsTask *self;

	self = GS_TASK (object);

	g_free (self->package_id);
	g_free (self->vendor_name);
	g_free (self->license_agreement);

	G_OBJECT_CLASS (gs_task_parent_class)->finalize (object);
}

static void
gs_task_class_init (GsTaskClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	PkTaskClass *task_class = PK_TASK_CLASS (klass);

	object_class->finalize = gs_task_finalize;
	task_class->untrusted_question = gs_task_untrusted_question;
	task_class->key_question = gs_task_key_question;
	task_class->eula_question = gs_task_eula_question;
	task_class->media_change_question = gs_task_media_change_question;

	signals[EULA_QUESTION] = g_signal_new ("eula-question",
					       G_TYPE_FROM_CLASS (klass),
					       G_SIGNAL_RUN_LAST,
					       0,
					       NULL,
					       NULL,
					       NULL,
					       G_TYPE_NONE,
					       1,
					       PK_TYPE_EULA_REQUIRED);
}

static void
gs_task_init (GsTask *self)
{
	self->package_id = NULL;
	self->vendor_name = NULL;
	self->license_agreement = NULL;
}

GsTask *
gs_task_new (void)
{
	return g_object_new (GS_TYPE_TASK, NULL);
}
