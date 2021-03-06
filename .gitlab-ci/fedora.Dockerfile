FROM fedora:31

RUN dnf -y install \
    clang \
    clang-analyzer \
    dbus-daemon \
    dbus-devel \
    desktop-file-utils \
    docbook-style-xsl \
    flatpak-devel \
    fwupd-devel \
    gcc \
    gettext \
    git \
    glib2-devel \
    gnome-desktop3-devel \
    gnome-online-accounts-devel \
    gobject-introspection \
    gobject-introspection-devel \
    gsettings-desktop-schemas-devel \
    gspell-devel \
    gtk-doc \
    gtk3-devel \
    json-glib-devel \
    itstool \
    lcov \
    libappstream-glib-devel \
    libdnf-devel \
    libgudev-devel \
    liboauth-devel \
    libsecret-devel \
    libsoup-devel \
    libxmlb-devel \
    libxslt \
    NetworkManager-libnm-devel \
    ninja-build \
    ostree-devel \
    PackageKit \
    PackageKit-glib-devel \
    pcre-devel \
    polkit-devel \
    python3 \
    python3-pip \
    python3-wheel \
    rpm-devel \
    rpm-ostree-devel \
    shared-mime-info \
    snapd-glib-devel \
    unzip \
    valgrind \
    valgrind-devel \
    wget \
    xz \
    zlib-devel \
 && dnf clean all

RUN pip3 install meson==0.47.0

ARG HOST_USER_ID=5555
ENV HOST_USER_ID ${HOST_USER_ID}
RUN useradd -u $HOST_USER_ID -ms /bin/bash user

ENV LANG C.UTF-8
