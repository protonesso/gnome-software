/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2019 Jonathan Kang <jonathankang@gnome.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

#include <gtk/gtk.h>

#include "gs-eula-dialog.h"

enum
{
    REJECT,
    ACCEPT,
    LAST_SIGNAL
};

struct _GsEulaDialog
{
    /*< private >*/
    GtkDialog parent_instance;
};

typedef struct
{
    GtkWidget *accept_button;
    GtkWidget *reject_button;
    GtkWidget *details_textview;
} GsEulaDialogPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (GsEulaDialog, gs_eula_dialog, GTK_TYPE_DIALOG)

static guint signals[LAST_SIGNAL] = { 0 };

void
gs_eula_dialog_populate_license_agreement (GsEulaDialog *self,
                                           const gchar *license_acceptment)
{
    g_autoptr(GtkTextBuffer) buffer = NULL;
    GsEulaDialogPrivate *priv;

    priv = gs_eula_dialog_get_instance_private (self);

    buffer = gtk_text_buffer_new (NULL);
    gtk_text_buffer_insert_at_cursor (buffer,
                                      license_acceptment, strlen (license_acceptment));
    gtk_text_view_set_buffer (GTK_TEXT_VIEW (priv->details_textview), buffer);
}

static void
gs_eula_dialog_response_cb (GtkDialog *dialog,
                            gint response_id,
                            gpointer user_data)
{
    GsEulaDialog *self = GS_EULA_DIALOG (dialog);

    if (response_id == GTK_RESPONSE_CANCEL)
    {
        g_signal_emit (self, signals[REJECT], 0);
    }

    if (response_id == GTK_RESPONSE_OK)
    {
        g_signal_emit (self, signals[ACCEPT], 0);
    }
}

static void
gs_eula_dialog_class_init (GsEulaDialogClass *klass)
{
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

    signals[REJECT] = g_signal_new ("reject",
                                    G_TYPE_FROM_CLASS (klass),
                                    G_SIGNAL_RUN_LAST,
                                    0,
                                    NULL,
                                    NULL,
                                    NULL,
                                    G_TYPE_NONE,
                                    0);

    signals[ACCEPT] = g_signal_new ("accept",
                                    G_TYPE_FROM_CLASS (klass),
                                    G_SIGNAL_RUN_LAST,
                                    0,
                                    NULL,
                                    NULL,
                                    NULL,
                                    G_TYPE_NONE,
                                    0);

    gtk_widget_class_set_template_from_resource (widget_class,
                                                 "/org/gnome/Software/gs-eula-dialog.ui");
    gtk_widget_class_bind_template_child_private (widget_class, GsEulaDialog,
                                                  accept_button);
    gtk_widget_class_bind_template_child_private (widget_class, GsEulaDialog,
                                                  reject_button);
    gtk_widget_class_bind_template_child_private (widget_class, GsEulaDialog,
                                                  details_textview);
    gtk_widget_class_bind_template_callback (widget_class, gs_eula_dialog_response_cb);
}

static void
gs_eula_dialog_init (GsEulaDialog *self)
{
    gtk_widget_init_template (GTK_WIDGET (self));
}

GsEulaDialog *
gs_eula_dialog_new (void)
{
    return g_object_new (GS_TYPE_EULA_DIALOG,
			 "use-header-bar", 1,
			 NULL);
}
