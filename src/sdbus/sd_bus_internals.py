# SPDX-License-Identifier: LGPL-2.1-or-later

# Copyright (C) 2020, 2021 igo95862

# This file is part of python-sdbus

# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.

# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
from __future__ import annotations

from asyncio import Future, Queue
from typing import (
    Any,
    Callable,
    Coroutine,
    Dict,
    List,
    Optional,
    Sequence,
    Tuple,
    Type,
    Union,
)

DbusBasicTypes = Union[str, int, bytes, float, Any]
DbusStructType = Tuple[DbusBasicTypes, ...]
DbusDictType = Dict[DbusBasicTypes, DbusBasicTypes]
DbusVariantType = Tuple[str, DbusStructType]
DbusListType = List[DbusBasicTypes]
DbusCompleteTypes = Union[DbusBasicTypes, DbusStructType,
                          DbusDictType, DbusVariantType, DbusListType]

__STUB_ERROR = (
    'Typing stub. You should never see this '
    'error unless the actual module failed to load. '
    'Check your installation.'
)


class SdBusSlot:
    """Holds reference to SdBus slot"""
    ...


class SdBusInterface:
    method_list: List[object]
    method_dict: Dict[bytes, object]
    property_list: List[object]
    property_get_dict: Dict[bytes, object]
    property_set_dict: Dict[bytes, object]
    signal_list: List[object]

    def add_method(
        self,
        member_name: str,
        signature: str, input_args_names: Sequence[str],
        result_signature: str, result_args_names: Sequence[str],
        flags: int,
        callback: Callable[[SdBusMessage], Coroutine[Any, Any, None]], /
    ) -> None:
        raise NotImplementedError(__STUB_ERROR)

    def add_property(
        self,
        property_name: str,
        property_signature: str,
        get_function: Callable[[SdBusMessage], Any],
        set_function: Optional[Callable[[SdBusMessage], None]],
        flags: int, /
    ) -> None:
        raise NotImplementedError(__STUB_ERROR)

    def add_signal(
        self,
        signal_name: str,
        signal_signature: str,
        signal_args_names: Sequence[str],
        flags: int, /
    ) -> None:
        raise NotImplementedError(__STUB_ERROR)


class SdBusMessage:
    def append_data(self, signature: str, *args: DbusCompleteTypes) -> None:
        raise NotImplementedError(__STUB_ERROR)

    def open_container(self, container_type: str,
                       container_signature: str, /) -> None:
        raise NotImplementedError(__STUB_ERROR)

    def close_container(self) -> None:
        raise NotImplementedError(__STUB_ERROR)

    def enter_container(self, container_type: str,
                        container_signature: str, /) -> None:
        raise NotImplementedError(__STUB_ERROR)

    def exit_container(self) -> None:
        raise NotImplementedError(__STUB_ERROR)

    def dump(self) -> None:
        raise NotImplementedError(__STUB_ERROR)

    def seal(
        self,
        cookie: Optional[int] = None,
        timeout_us: Optional[int] = None
    ) -> None:
        raise NotImplementedError(__STUB_ERROR)

    def get_contents(self
                     ) -> Tuple[DbusCompleteTypes, ...]:
        raise NotImplementedError(__STUB_ERROR)

    def get_credentials(self) -> SdBusCreds:
        raise NotImplementedError(__STUB_ERROR)

    def create_reply(self) -> SdBusMessage:
        raise NotImplementedError(__STUB_ERROR)

    def create_error_reply(
            self,
            error_name: str,
            error_message: str, /) -> SdBusMessage:
        raise NotImplementedError(__STUB_ERROR)

    def send(self) -> None:
        raise NotImplementedError(__STUB_ERROR)

    expect_reply: bool = False
    cookie: int
    destination: Optional[str] = None
    path: Optional[str] = None
    interface: Optional[str] = None
    member: Optional[str] = None
    sender: Optional[str] = None


class SdBusCreds:

    @property
    def mask(self) -> Optional[int]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def pid(self) -> Optional[int]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def ppid(self) -> Optional[int]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def tid(self) -> Optional[int]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def uid(self) -> Optional[int]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def euid(self) -> Optional[int]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def suid(self) -> Optional[int]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def fsuid(self) -> Optional[int]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def gid(self) -> Optional[int]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def egid(self) -> Optional[int]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def sgid(self) -> Optional[int]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def fsgid(self) -> Optional[int]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def supplementary_gids(self) -> Optional[tuple[int, ...]]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def comm(self) -> Optional[str]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def tid_comm(self) -> Optional[str]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def exe(self) -> Optional[str]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def cmdline(self) -> Optional[tuple[str, ...]]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def cgroup(self) -> Optional[str]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def unit(self) -> Optional[str]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def slice(self) -> Optional[str]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def user_unit(self) -> Optional[str]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def user_slice(self) -> Optional[str]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def session(self) -> Optional[str]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def owner_uid(self) -> Optional[int]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def selinux_context(self) -> Optional[str]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def audit_session_id(self) -> Optional[int]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def audit_login_uid(self) -> Optional[int]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def tty(self) -> Optional[str]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def unique_name(self) -> Optional[str]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def well_known_names(self) -> Optional[tuple[str, ...]]:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def description(self) -> Optional[str]:
        raise NotImplementedError(__STUB_ERROR)

    def has_effective_cap(self, capability: int) -> Optional[bool]:
        raise NotImplementedError(__STUB_ERROR)

    def has_permitted_cap(self, capability: int) -> Optional[bool]:
        raise NotImplementedError(__STUB_ERROR)

    def has_inheritable_cap(self, capability: int) -> Optional[bool]:
        raise NotImplementedError(__STUB_ERROR)

    def has_bounding_cap(self, capability: int) -> Optional[bool]:
        raise NotImplementedError(__STUB_ERROR)


class SdBus:
    def call(self, message: SdBusMessage, /) -> SdBusMessage:
        raise NotImplementedError(__STUB_ERROR)

    def call_async(
            self, message: SdBusMessage,
            /) -> Future[SdBusMessage]:
        raise NotImplementedError(__STUB_ERROR)

    def drive(self) -> None:
        raise NotImplementedError(__STUB_ERROR)

    def get_fd(self) -> int:
        raise NotImplementedError(__STUB_ERROR)

    def new_method_call_message(
            self,
            destination_name: str, object_path: str,
            interface_name: str, member_name: str,
            /) -> SdBusMessage:
        raise NotImplementedError(__STUB_ERROR)

    def new_property_get_message(
            self,
            destination_service_name: str, object_path: str,
            interface_name: str, member_name: str,
            /) -> SdBusMessage:
        raise NotImplementedError(__STUB_ERROR)

    def new_property_set_message(
            self,
            destination_service_name: str, object_path: str,
            interface_name: str, member_name: str,
            /) -> SdBusMessage:
        raise NotImplementedError(__STUB_ERROR)

    def new_signal_message(
            self,
            object_path: str,
            interface_name: str,
            member_name: str,
            /) -> SdBusMessage:
        raise NotImplementedError(__STUB_ERROR)

    def add_interface(self, new_interface: SdBusInterface,
                      object_path: str, interface_name: str, /) -> None:
        raise NotImplementedError(__STUB_ERROR)

    def get_signal_queue_async(
        self,
        senders_name: Optional[str], object_path: Optional[str],
        interface_name: Optional[str], member_name: Optional[str],
        /
    ) -> Future[Queue[SdBusMessage]]:
        raise NotImplementedError(__STUB_ERROR)

    def request_name_async(self, name: str, flags: int, /) -> Future[None]:
        raise NotImplementedError(__STUB_ERROR)

    def request_name(self, name: str, flags: int, /) -> None:
        raise NotImplementedError(__STUB_ERROR)

    @property
    def unique_name(self) -> str:
        raise NotImplementedError(__STUB_ERROR)

    def add_object_manager(self, path: str, /) -> SdBusSlot:
        raise NotImplementedError(__STUB_ERROR)

    def emit_object_added(self, path: str, /) -> None:
        raise NotImplementedError(__STUB_ERROR)

    def emit_object_removed(self, path: str, /) -> None:
        raise NotImplementedError(__STUB_ERROR)

    def close(self) -> None:
        raise NotImplementedError(__STUB_ERROR)

    def start(self) -> None:
        raise NotImplementedError(__STUB_ERROR)

    address: Optional[str] = None

    def set_method_call_timeout(self, timeout_usec: int) -> None:
        raise NotImplementedError(__STUB_ERROR)

    def get_method_call_timeout(self) -> int:
        raise NotImplementedError(__STUB_ERROR)

    def negotiate_creds(self, mask_on: bool, mask: int) -> None:
        raise NotImplementedError(__STUB_ERROR)

    def get_creds_mask(self) -> int:
        raise NotImplementedError(__STUB_ERROR)


def sd_bus_open() -> SdBus:
    raise NotImplementedError(__STUB_ERROR)


def sd_bus_open_user() -> SdBus:
    raise NotImplementedError(__STUB_ERROR)


def sd_bus_open_system() -> SdBus:
    raise NotImplementedError(__STUB_ERROR)


def sd_bus_open_system_remote(host: str, /) -> SdBus:
    raise NotImplementedError(__STUB_ERROR)


def sd_bus_open_user_machine(machine: str, /) -> SdBus:
    raise NotImplementedError(__STUB_ERROR)


def sd_bus_open_system_machine(machine: str, /) -> SdBus:
    raise NotImplementedError(__STUB_ERROR)


def encode_object_path(prefix: str, external: str) -> str:
    raise NotImplementedError(__STUB_ERROR)


def decode_object_path(prefix: str, full_path: str) -> str:
    raise NotImplementedError(__STUB_ERROR)


def map_exception_to_dbus_error(exc: Type[Exception],
                                dbus_error_name: str, /) -> None:
    ...  # We want to be able to generate docs without module


def add_exception_mapping(exc: Exception, /) -> None:
    ...  # We want to be able to generate docs without module


def is_interface_name_valid(string_to_check: str, /) -> bool:
    raise NotImplementedError(__STUB_ERROR)


def is_service_name_valid(string_to_check: str, /) -> bool:
    raise NotImplementedError(__STUB_ERROR)


def is_member_name_valid(string_to_check: str, /) -> bool:
    raise NotImplementedError(__STUB_ERROR)


def is_object_path_valid(string_to_check: str, /) -> bool:
    raise NotImplementedError(__STUB_ERROR)


class SdBusBaseError(Exception):
    ...


class SdBusUnmappedMessageError(SdBusBaseError):
    ...


class SdBusLibraryError(SdBusBaseError):
    ...


DBUS_ERROR_TO_EXCEPTION: Dict[str, Exception] = {}

EXCEPTION_TO_DBUS_ERROR: Dict[Exception, str] = {}

DbusDeprecatedFlag: int = 0
DbusHiddenFlag: int = 0
DbusUnprivilegedFlag: int = 0
DbusNoReplyFlag: int = 0
DbusPropertyConstFlag: int = 0
DbusPropertyEmitsChangeFlag: int = 0
DbusPropertyEmitsInvalidationFlag: int = 0
DbusPropertyExplicitFlag: int = 0
DbusSensitiveFlag: int = 0


DbusCredTypePID: int = 0
DbusCredTypeTID: int = 0
DbusCredTypePPID: int = 0
DbusCredTypeUID: int = 0
DbusCredTypeEUID: int = 0
DbusCredTypeSUID: int = 0
DbusCredTypeFSUID: int = 0
DbusCredTypeGID: int = 0
DbusCredTypeEGID: int = 0
DbusCredTypeSGID: int = 0
DbusCredTypeFSGID: int = 0
DbusCredTypeSupplementaryGIDs: int = 0
DbusCredTypeComm: int = 0
DbusCredTypeTIDComm: int = 0
DbusCredTypeEXE: int = 0
DbusCredTypeCmdline: int = 0
DbusCredTypeCGroup: int = 0
DbusCredTypeUnit: int = 0
DbusCredTypeSlice: int = 0
DbusCredTypeUserUnit: int = 0
DbusCredTypeUserSlice: int = 0
DbusCredTypeSession: int = 0
DbusCredTypeOwnerUID: int = 0
DbusCredTypeEffectiveCaps: int = 0
DbusCredTypePermittedCaps: int = 0
DbusCredTypeInheritableCaps: int = 0
DbusCredTypeBoundingCaps: int = 0
DbusCredTypeSelinuxContext: int = 0
DbusCredTypeAuditSessionId: int = 0
DbusCredTypeAuditLoginUID: int = 0
DbusCredTypeTTY: int = 0
DbusCredTypeUniqueName: int = 0
DbusCredTypeWellKnownNames: int = 0
DbusCredTypeDescription: int = 0
DbusCredTypeAugment: int = 0
DbusAllCredTypes: int = 0
