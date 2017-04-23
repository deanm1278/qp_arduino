/*******************************************************************************
 * Copyright (C) Lawrence Lo (https://github.com/galliumstudio). 
 * All rights reserved.
 *
 * This program is open source software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

/*
* Individual events would all be defined here
*/

#ifndef EVENT_H
#define EVENT_H

#include "qpcpp.h"
#include "qp_extras.h"

#define LOG_EVENT(e_)            Log::Event(me->m_name, __FUNCTION__, GetEvtName(e_->sig), e_->sig);

using namespace FW;

enum {
    SYSTEM_START_REQ = QP::Q_USER_SIG,
    SYSTEM_START_CFM,
    SYSTEM_STOP_REQ,
    SYSTEM_STOP_CFM,
    SYSTEM_TEST_TIMER,
    SYSTEM_DONE,
    SYSTEM_FAIL,
    
    USER_LED_TOGGLE_REQ,
    
    MAX_PUB_SIG
};

char const * GetEvtName(QP::QSignal sig);

class SystemStartReq : public Evt {
public:
    enum {
        TIMEOUT_MS = 600
    };
    SystemStartReq(uint16_t seq) :
        Evt(SYSTEM_START_REQ, seq) {}
};

class SystemStartCfm : public ErrorEvt {
public:
    SystemStartCfm(uint16_t seq, Error error, Reason reason = 0) :
        ErrorEvt(SYSTEM_START_CFM, seq, error, reason) {}
};

class SystemStopReq : public Evt {
public:
    enum {
        TIMEOUT_MS = 600
    };
    SystemStopReq(uint16_t seq) :
        Evt(SYSTEM_STOP_REQ, seq) {}
};

class SystemStopCfm : public ErrorEvt {
public:
    SystemStopCfm(uint16_t seq, Error error, Reason reason = 0) :
        ErrorEvt(SYSTEM_STOP_CFM, seq, error, reason) {}
};

class SystemFail : public ErrorEvt {
public:
    SystemFail(Error error, Reason reason) :
        ErrorEvt(SYSTEM_FAIL, 0, error, reason) {}
};

class UserLedToggleReq : public Evt {
public:
    enum {
        TIMEOUT_MS = 100
    };
    UserLedToggleReq(uint16_t seq) :
        Evt(USER_LED_TOGGLE_REQ, seq) {}
};

#endif