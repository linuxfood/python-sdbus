// SPDX-License-Identifier: LGPL-2.1-or-later
/*
    Copyright (C) 2020, 2021 igo95862

    This file is part of python-sdbus

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
*/
#include "sd_bus_internals.h"

static int SdBusCreds_init(SdBusCredsObject* self, PyObject* Py_UNUSED(args), PyObject* Py_UNUSED(kwds)) {
        self->creds_ref = NULL;
        return 0;
}

void _SdBusCreds_set_creds_from_message(SdBusCredsObject* self, sd_bus_message* message) {
        self->creds_ref = sd_bus_creds_ref(sd_bus_message_get_creds(message));
}

typedef struct {
        const char* name;
        uint64_t flag;
} _SdBus_cred_named;

static _SdBus_cred_named _SdBus_all_cred_types[] = {
    {"DbusCredTypePID", SD_BUS_CREDS_PID},
    {"DbusCredTypeTID", SD_BUS_CREDS_TID},
    {"DbusCredTypePPID", SD_BUS_CREDS_PPID},
    {"DbusCredTypeUID", SD_BUS_CREDS_UID},
    {"DbusCredTypeEUID", SD_BUS_CREDS_EUID},
    {"DbusCredTypeSUID", SD_BUS_CREDS_SUID},
    {"DbusCredTypeFSUID", SD_BUS_CREDS_FSUID},
    {"DbusCredTypeGID", SD_BUS_CREDS_GID},
    {"DbusCredTypeEGID", SD_BUS_CREDS_EGID},
    {"DbusCredTypeSGID", SD_BUS_CREDS_SGID},
    {"DbusCredTypeFSGID", SD_BUS_CREDS_FSGID},
    {"DbusCredTypeSupplementaryGIDs", SD_BUS_CREDS_SUPPLEMENTARY_GIDS},
    {"DbusCredTypeComm", SD_BUS_CREDS_COMM},
    {"DbusCredTypeTIDComm", SD_BUS_CREDS_TID_COMM},
    {"DbusCredTypeEXE", SD_BUS_CREDS_EXE},
    {"DbusCredTypeCmdline", SD_BUS_CREDS_CMDLINE},
    {"DbusCredTypeCGroup", SD_BUS_CREDS_CGROUP},
    {"DbusCredTypeUnit", SD_BUS_CREDS_UNIT},
    {"DbusCredTypeSlice", SD_BUS_CREDS_SLICE},
    {"DbusCredTypeUserUnit", SD_BUS_CREDS_USER_UNIT},
    {"DbusCredTypeUserSlice", SD_BUS_CREDS_USER_SLICE},
    {"DbusCredTypeSession", SD_BUS_CREDS_SESSION},
    {"DbusCredTypeOwnerUID", SD_BUS_CREDS_OWNER_UID},
    {"DbusCredTypeEffectiveCaps", SD_BUS_CREDS_EFFECTIVE_CAPS},
    {"DbusCredTypePermittedCaps", SD_BUS_CREDS_PERMITTED_CAPS},
    {"DbusCredTypeInheritableCaps", SD_BUS_CREDS_INHERITABLE_CAPS},
    {"DbusCredTypeBoundingCaps", SD_BUS_CREDS_BOUNDING_CAPS},
    {"DbusCredTypeSelinuxContext", SD_BUS_CREDS_SELINUX_CONTEXT},
    {"DbusCredTypeAuditSessionId", SD_BUS_CREDS_AUDIT_SESSION_ID},
    {"DbusCredTypeAuditLoginUID", SD_BUS_CREDS_AUDIT_LOGIN_UID},
    {"DbusCredTypeTTY", SD_BUS_CREDS_TTY},
    {"DbusCredTypeUniqueName", SD_BUS_CREDS_UNIQUE_NAME},
    {"DbusCredTypeWellKnownNames", SD_BUS_CREDS_WELL_KNOWN_NAMES},
    {"DbusCredTypeDescription", SD_BUS_CREDS_DESCRIPTION},
    {"DbusCredTypeAugment", SD_BUS_CREDS_AUGMENT},
    {"DbusAllCredTypes", _SD_BUS_CREDS_ALL},
};

static const int n_cred_types = sizeof(_SdBus_all_cred_types) / sizeof(_SdBus_all_cred_types[0]);

PyObject* _SdBusCreds_sdbus_module_init(PyObject* m) {
        for (int i = 0; i < n_cred_types; i++) {
                const char* name = _SdBus_all_cred_types[i].name;
                const uint64_t flag = _SdBus_all_cred_types[i].flag;
                CALL_PYTHON_INT_CHECK(PyModule_AddIntConstant(m, name, flag));
        }
        return m;
}

static void SdBusCreds_dealloc(SdBusCredsObject* self) {
        sd_bus_creds_unref(self->creds_ref);

        SD_BUS_DEALLOC_TAIL;
}

static PyObject* SdBusCreds_mask_getter(SdBusCredsObject* self, void* Py_UNUSED(closure)) {
        return PyLong_FromUnsignedLongLong(sd_bus_creds_get_mask(self->creds_ref));
}

static PyObject* SdBusCreds_get_pid(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        pid_t out;
        if (sd_bus_creds_get_pid(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyLong_FromUnsignedLongLong(out);
}

static PyObject* SdBusCreds_get_ppid(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        pid_t out;
        if (sd_bus_creds_get_ppid(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyLong_FromUnsignedLongLong(out);
}

static PyObject* SdBusCreds_get_tid(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        pid_t out;
        if (sd_bus_creds_get_tid(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyLong_FromUnsignedLongLong(out);
}

static PyObject* SdBusCreds_get_uid(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        uid_t out;
        if (sd_bus_creds_get_uid(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyLong_FromUnsignedLongLong(out);
}

static PyObject* SdBusCreds_get_euid(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        uid_t out;
        if (sd_bus_creds_get_euid(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyLong_FromUnsignedLongLong(out);
}

static PyObject* SdBusCreds_get_suid(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        uid_t out;
        if (sd_bus_creds_get_suid(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyLong_FromUnsignedLongLong(out);
}

static PyObject* SdBusCreds_get_fsuid(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        uid_t out;
        if (sd_bus_creds_get_fsuid(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyLong_FromUnsignedLongLong(out);
}

static PyObject* SdBusCreds_get_gid(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        gid_t out;
        if (sd_bus_creds_get_gid(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyLong_FromUnsignedLongLong(out);
}

static PyObject* SdBusCreds_get_egid(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        gid_t out;
        if (sd_bus_creds_get_egid(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyLong_FromUnsignedLongLong(out);
}

static PyObject* SdBusCreds_get_sgid(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        gid_t out;
        if (sd_bus_creds_get_sgid(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyLong_FromUnsignedLongLong(out);
}

static PyObject* SdBusCreds_get_fsgid(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        gid_t out;
        if (sd_bus_creds_get_fsgid(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyLong_FromUnsignedLongLong(out);
}

static PyObject* SdBusCreds_get_supplementary_gids(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        const gid_t* gids = NULL;
        const int n_gids = sd_bus_creds_get_supplementary_gids(self->creds_ref, &gids);
        if (n_gids < 0) {
                return PyTuple_New(0);
        }

        PyObject* result CLEANUP_PY_OBJECT = CALL_PYTHON_AND_CHECK(PyTuple_New(n_gids));
        for (int i = 0; i < n_gids; i++) {
                PyObject* new_object CLEANUP_PY_OBJECT = CALL_PYTHON_AND_CHECK(PyLong_FromUnsignedLong(gids[i]));
                CALL_PYTHON_INT_CHECK(PyTuple_SetItem(result, i, new_object));
        }
        return PyList_AsTuple(result);
}

static PyObject* SdBusCreds_get_comm(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        const char* out = NULL;
        if (sd_bus_creds_get_comm(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyUnicode_FromString(out);
}

static PyObject* SdBusCreds_get_tid_comm(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        const char* out = NULL;
        if (sd_bus_creds_get_tid_comm(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyUnicode_FromString(out);
}

static PyObject* SdBusCreds_get_exe(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        const char* out = NULL;
        if (sd_bus_creds_get_exe(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyUnicode_FromString(out);
}

static PyObject* SdBusCreds_get_cmdline(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        char** out = NULL;
        if (sd_bus_creds_get_cmdline(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        PyObject* new_list CLEANUP_PY_OBJECT = CALL_PYTHON_AND_CHECK(PyList_New(0));
        char** argv = out;
        while (*argv != NULL) {
                PyObject* new_object CLEANUP_PY_OBJECT = CALL_PYTHON_AND_CHECK(PyUnicode_FromString(*argv));
                CALL_PYTHON_INT_CHECK(PyList_Append(new_list, new_object));
                argv++;
        }
        return PyList_AsTuple(new_list);
}

static PyObject* SdBusCreds_get_cgroup(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        const char* out = NULL;
        if (sd_bus_creds_get_cgroup(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyUnicode_FromString(out);
}

static PyObject* SdBusCreds_get_unit(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        const char* out = NULL;
        if (sd_bus_creds_get_unit(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyUnicode_FromString(out);
}

static PyObject* SdBusCreds_get_slice(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        const char* out = NULL;
        if (sd_bus_creds_get_slice(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyUnicode_FromString(out);
}

static PyObject* SdBusCreds_get_user_unit(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        const char* out = NULL;
        if (sd_bus_creds_get_user_unit(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyUnicode_FromString(out);
}

static PyObject* SdBusCreds_get_user_slice(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        const char* out = NULL;
        if (sd_bus_creds_get_user_slice(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyUnicode_FromString(out);
}

static PyObject* SdBusCreds_get_session(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        const char* out = NULL;
        if (sd_bus_creds_get_session(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyUnicode_FromString(out);
}

static PyObject* SdBusCreds_get_owner_uid(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        uid_t out = -1;
        if (sd_bus_creds_get_owner_uid(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyLong_FromUnsignedLong(out);
}

#ifndef Py_LIMITED_API
static PyObject* SdBusCreds_has_effective_cap(SdBusCredsObject* self, PyObject* const* args, Py_ssize_t nargs) {
        SD_BUS_PY_CHECK_ARGS_NUMBER(1);
        SD_BUS_PY_CHECK_ARG_CHECK_FUNC(0, PyLong_Check);
        int capability = PyLong_AsLong(args[0]);
#else
static PyObject* SdBusCreds_has_effective_cap(SdBusCredsObject* self, PyObject* args) {
        int capability = -1;
        CALL_PYTHON_BOOL_CHECK(PyArg_ParseTuple(args, "i", &capability, NULL));
#endif
        int result = sd_bus_creds_has_effective_cap(self->creds_ref, capability);
        if (result < 0) {
                Py_RETURN_NONE;
        }
        return PyBool_FromLong(result);
}

#ifndef Py_LIMITED_API
static PyObject* SdBusCreds_has_permitted_cap(SdBusCredsObject* self, PyObject* const* args, Py_ssize_t nargs) {
        SD_BUS_PY_CHECK_ARGS_NUMBER(1);
        SD_BUS_PY_CHECK_ARG_CHECK_FUNC(0, PyLong_Check);
        int capability = PyLong_AsLong(args[0]);
#else
static PyObject* SdBusCreds_has_permitted_cap(SdBusCredsObject* self, PyObject* args) {
        int capability = -1;
        CALL_PYTHON_BOOL_CHECK(PyArg_ParseTuple(args, "i", &capability, NULL));
#endif
        int result = sd_bus_creds_has_permitted_cap(self->creds_ref, capability);
        if (result < 0) {
                Py_RETURN_NONE;
        }
        return PyBool_FromLong(result);
}

#ifndef Py_LIMITED_API
static PyObject* SdBusCreds_has_inheritable_cap(SdBusCredsObject* self, PyObject* const* args, Py_ssize_t nargs) {
        SD_BUS_PY_CHECK_ARGS_NUMBER(1);
        SD_BUS_PY_CHECK_ARG_CHECK_FUNC(0, PyLong_Check);
        int capability = PyLong_AsLong(args[0]);
#else
static PyObject* SdBusCreds_has_inheritable_cap(SdBusCredsObject* self, PyObject* args) {
        int capability = -1;
        CALL_PYTHON_BOOL_CHECK(PyArg_ParseTuple(args, "i", &capability, NULL));
#endif
        int result = sd_bus_creds_has_inheritable_cap(self->creds_ref, capability);
        if (result < 0) {
                Py_RETURN_NONE;
        }
        return PyBool_FromLong(result);
}

#ifndef Py_LIMITED_API
static PyObject* SdBusCreds_has_bounding_cap(SdBusCredsObject* self, PyObject* const* args, Py_ssize_t nargs) {
        SD_BUS_PY_CHECK_ARGS_NUMBER(1);
        SD_BUS_PY_CHECK_ARG_CHECK_FUNC(0, PyLong_Check);
        int capability = PyLong_AsLong(args[0]);
#else
static PyObject* SdBusCreds_has_bounding_cap(SdBusCredsObject* self, PyObject* args) {
        int capability = -1;
        CALL_PYTHON_BOOL_CHECK(PyArg_ParseTuple(args, "i", &capability, NULL));
#endif
        int result = sd_bus_creds_has_bounding_cap(self->creds_ref, capability);
        if (result < 0) {
                Py_RETURN_NONE;
        }
        return PyBool_FromLong(result);
}

static PyObject* SdBusCreds_get_selinux_context(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        const char* out = NULL;
        if (sd_bus_creds_get_selinux_context(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyUnicode_FromString(out);
}
static PyObject* SdBusCreds_get_audit_session_id(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        uint32_t out = -1;
        if (sd_bus_creds_get_audit_session_id(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyLong_FromUnsignedLong(out);
}
static PyObject* SdBusCreds_get_audit_login_uid(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        uid_t out = -1;
        if (sd_bus_creds_get_audit_login_uid(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyLong_FromUnsignedLong(out);
}

static PyObject* SdBusCreds_get_tty(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        const char* out = NULL;
        if (sd_bus_creds_get_tty(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyUnicode_FromString(out);
}

static PyObject* SdBusCreds_get_unique_name(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        const char* out = NULL;
        if (sd_bus_creds_get_unique_name(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyUnicode_FromString(out);
}

static PyObject* SdBusCreds_get_well_known_names(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        char** out = NULL;
        if (sd_bus_creds_get_well_known_names(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        PyObject* new_list CLEANUP_PY_OBJECT = CALL_PYTHON_AND_CHECK(PyList_New(0));
        char** argv = out;
        while (*argv != NULL) {
                PyObject* new_object CLEANUP_PY_OBJECT = CALL_PYTHON_AND_CHECK(PyUnicode_FromString(*argv));
                CALL_PYTHON_INT_CHECK(PyList_Append(new_list, new_object));
                argv++;
        }
        return PyList_AsTuple(new_list);
}

static PyObject* SdBusCreds_get_description(SdBusCredsObject* self, PyObject* Py_UNUSED(args)) {
        const char* out = NULL;
        if (sd_bus_creds_get_description(self->creds_ref, &out) < 0) {
                Py_RETURN_NONE;
        }
        return PyUnicode_FromString(out);
}

static PyGetSetDef SdBusCreds_properies[] = {
    {"mask", (getter)SdBusCreds_mask_getter, NULL, "mask of available credential fields", NULL},
    {"pid", (getter)SdBusCreds_get_pid, NULL, "pid of the credential or None", NULL},
    {"ppid", (getter)SdBusCreds_get_ppid, NULL, "ppid of the credential or None", NULL},
    {"tid", (getter)SdBusCreds_get_tid, NULL, "tid of the credential or None", NULL},
    {"uid", (getter)SdBusCreds_get_uid, NULL, "uid of the credential or None", NULL},
    {"euid", (getter)SdBusCreds_get_euid, NULL, "euid of the credential or None", NULL},
    {"suid", (getter)SdBusCreds_get_suid, NULL, "suid of the credential or None", NULL},
    {"fsuid", (getter)SdBusCreds_get_fsuid, NULL, "fsuid of the credential or None", NULL},
    {"gid", (getter)SdBusCreds_get_gid, NULL, "gid of the credential or None", NULL},
    {"egid", (getter)SdBusCreds_get_egid, NULL, "egid of the credential or None", NULL},
    {"sgid", (getter)SdBusCreds_get_sgid, NULL, "sgid of the credential or None", NULL},
    {"fsgid", (getter)SdBusCreds_get_fsgid, NULL, "fsgid of the credential or None", NULL},
    {"supplementary_gids", (getter)SdBusCreds_get_supplementary_gids, NULL, "possibly empty tuple of supplementary gids of the credential", NULL},
    {"comm", (getter)SdBusCreds_get_comm, NULL, "comm of the credential or None", NULL},
    {"tid_comm", (getter)SdBusCreds_get_tid_comm, NULL, "tid_comm of the credential or None", NULL},
    {"exe", (getter)SdBusCreds_get_exe, NULL, "exe of the credential or None", NULL},
    {"cmdline", (getter)SdBusCreds_get_cmdline, NULL, "possibly empty tuple of cmdline arguments of the credential", NULL},
    {"cgroup", (getter)SdBusCreds_get_cgroup, NULL, "cgroup of the credential or None", NULL},
    {"unit", (getter)SdBusCreds_get_unit, NULL, "unit of the credential or None", NULL},
    {"slice", (getter)SdBusCreds_get_slice, NULL, "slice of the credential or None", NULL},
    {"user_unit", (getter)SdBusCreds_get_user_unit, NULL, "user unit of the credential or None", NULL},
    {"user_slice", (getter)SdBusCreds_get_user_slice, NULL, "user slice of the credential or None", NULL},
    {"session", (getter)SdBusCreds_get_session, NULL, "session of the credential or None", NULL},
    {"owner_uid", (getter)SdBusCreds_get_owner_uid, NULL, "owner uid of the credential or None", NULL},
    {"selinux_context", (getter)SdBusCreds_get_selinux_context, NULL, "selinux context of the credential or None", NULL},
    {"audit_session_id", (getter)SdBusCreds_get_audit_session_id, NULL, "audit session id of the credential or None", NULL},
    {"audit_login_uid", (getter)SdBusCreds_get_audit_login_uid, NULL, "audit_login_uid of the credential or None", NULL},
    {"tty", (getter)SdBusCreds_get_tty, NULL, "tty of the credential or None", NULL},
    {"unique_name", (getter)SdBusCreds_get_unique_name, NULL, "unique bus name of the credential or None", NULL},
    {"well_known_names", (getter)SdBusCreds_get_well_known_names, NULL, "possibly empty tuple of well known names of the credential", NULL},
    {"description", (getter)SdBusCreds_get_description, NULL, "description of the credential or None", NULL},
    {0},
};

static PyMethodDef SdBusCreds_methods[] = {
    {"has_effective_cap", (SD_BUS_PY_FUNC_TYPE)SdBusCreds_has_effective_cap, SD_BUS_PY_METH, ""},
    {"has_permitted_cap", (SD_BUS_PY_FUNC_TYPE)SdBusCreds_has_permitted_cap, SD_BUS_PY_METH, ""},
    {"has_inheritable_cap", (SD_BUS_PY_FUNC_TYPE)SdBusCreds_has_inheritable_cap, SD_BUS_PY_METH, ""},
    {"has_bounding_cap", (SD_BUS_PY_FUNC_TYPE)SdBusCreds_has_bounding_cap, SD_BUS_PY_METH, ""},
    {NULL, NULL, 0, NULL},
};

PyType_Spec SdBusCredsType = {
    .name = "sd_bus_internals.SdBusCreds",
    .basicsize = sizeof(SdBusCredsObject),
    .itemsize = 0,
    .flags = Py_TPFLAGS_DEFAULT,
    .slots =
        (PyType_Slot[]){
            {Py_tp_init, (initproc)SdBusCreds_init},
            {Py_tp_dealloc, (destructor)SdBusCreds_dealloc},
            {Py_tp_methods, SdBusCreds_methods},
            {Py_tp_getset, SdBusCreds_properies},
            {0, NULL},
        },
};
