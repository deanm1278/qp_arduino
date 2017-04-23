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
* This is an example class for an active object
*/

#ifndef SYSTEM_H
#define SYSTEM_H

#include "qpcpp.h"
#include "qp_extras.h"

#include "hsm_id.h"

#define LEDPIN 13

using namespace QP;
using namespace FW;

class System : public QActive {
public:
    System();
    void Start(uint8_t prio) {
        QActive::start(prio, m_evtQueueStor, ARRAY_COUNT(m_evtQueueStor), NULL, 0);
    }

protected:
    static QState InitialPseudoState(System * const me, QEvt const * const e);
    static QState Root(System * const me, QEvt const * const e);
    static QState Stopped(System * const me, QEvt const * const e);
    static QState Started(System * const me, QEvt const * const e);

    enum {
        EVT_QUEUE_COUNT = 16,
        DEFER_QUEUE_COUNT = 4
    };
    QEvt const *m_evtQueueStor[EVT_QUEUE_COUNT];
    QEvt const *m_deferQueueStor[DEFER_QUEUE_COUNT];
    QEQueue m_deferQueue;
    uint8_t m_id;
    char const * m_name;
	
    QTimeEvt m_testTimer;
    
};


#endif // SYSTEM_H


