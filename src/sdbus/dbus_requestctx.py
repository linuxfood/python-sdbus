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
from contextvars import ContextVar, Token
from typing import Generic, Optional, Type, TypeVar

from sdbus.sd_bus_internals import SdBusCreds

_T = TypeVar("_T")
_U = TypeVar("_U")


class RequestVar(Generic[_T]):
    def __init__(self, name: str) -> None:
        self.var = ContextVar[_T](name)

    def set(self, new_value: _T) -> Token[_T]:
        return self.var.set(new_value)

    def reset(self, token: Token[_T]) -> None:
        self.var.reset(token)

    def __get__(self, _instance: _U, _owner: Optional[Type[_U]] = None) -> _T:
        return self.var.get()


MESSAGE_SENDER_VAR = RequestVar[str]("request sender")
MESSAGE_CREDS_VAR = RequestVar[SdBusCreds]("request credentials")


class DbusRequestContext:

    sender = MESSAGE_SENDER_VAR
    credentials = MESSAGE_CREDS_VAR
