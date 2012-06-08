/* Ruby/SerialPort $Id$
 * Guillaume Pierronnet <moumar@netcourrier.com>
 * Alan Stern <stern@rowland.harvard.edu>
 * Daniel E. Shipton <dshipton@redshiptechnologies.com>
 * Tobin Richard <tobin.richard@gmail.com>
 *
 * This code is hereby licensed for public consumption under either the
 * GNU GPL v2 or greater.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * For documentation on serial programming, see the excellent:
 * "Serial Programming Guide for POSIX Operating Systems"
 * written Michael R. Sweet.
 * http://www.easysw.com/~mike/serial/
 */

#ifndef _RUBY_SERIAL_PORT_H_
#define _RUBY_SERIAL_PORT_H_

#define RUBY_SERIAL_PORT_VERSION   "0.7.2"

#include <mruby.h>    /* ruby inclusion */
//#include <rubyio.h>  /* ruby io inclusion */

struct modem_params
{
  int data_rate;
  int data_bits;
  int stop_bits;
  int parity;
};

struct line_signals
{
  int rts;
  int dtr;
  int cts;
  int dsr;
  int dcd;
  int ri;
};

#define NONE   0
#define HARD   1
#define SOFT   2

#if defined(OS_MSWIN) || defined(OS_BCCWIN)
#define SPACE  SPACEPARITY
#define MARK   MARKPARITY
#define EVEN   EVENPARITY
#define ODD    ODDPARITY

#ifndef RB_SERIAL_EXPORT
#define RB_SERIAL_EXPORT __declspec(dllexport)
#endif
#else
#define SPACE  0
#define MARK   0
#define EVEN   1
#define ODD    2

#define RB_SERIAL_EXPORT
#endif

extern mrb_value sBaud, sDataBits, sStopBits, sParity; /* strings */
extern mrb_value sRts, sDtr, sCts, sDsr, sDcd, sRi;

/* Implementation specific functions. */
mrb_value RB_SERIAL_EXPORT sp_create_impl(mrb_value class, mrb_value _port);
mrb_value RB_SERIAL_EXPORT sp_set_modem_params_impl(int argc, mrb_value *argv, mrb_value self);
void RB_SERIAL_EXPORT get_modem_params_impl(mrb_value self, struct modem_params *mp);
mrb_value RB_SERIAL_EXPORT sp_set_flow_control_impl(mrb_value self, mrb_value val);
mrb_value RB_SERIAL_EXPORT sp_get_flow_control_impl(mrb_value self);
mrb_value RB_SERIAL_EXPORT sp_set_read_timeout_impl(mrb_value self, mrb_value val);
mrb_value RB_SERIAL_EXPORT sp_get_read_timeout_impl(mrb_value self);
mrb_value RB_SERIAL_EXPORT sp_set_write_timeout_impl(mrb_value self, mrb_value val);
mrb_value RB_SERIAL_EXPORT sp_get_write_timeout_impl(mrb_value self);
mrb_value RB_SERIAL_EXPORT sp_break_impl(mrb_value self, mrb_value time);
void RB_SERIAL_EXPORT get_line_signals_helper_impl(mrb_value obj, struct line_signals *ls);
mrb_value RB_SERIAL_EXPORT set_signal_impl(mrb_value obj, mrb_value val, int sig);
mrb_value RB_SERIAL_EXPORT sp_set_rts_impl(mrb_value self, mrb_value val);
mrb_value RB_SERIAL_EXPORT sp_set_dtr_impl(mrb_value self, mrb_value val);
mrb_value RB_SERIAL_EXPORT sp_get_rts_impl(mrb_value self);
mrb_value RB_SERIAL_EXPORT sp_get_dtr_impl(mrb_value self);

#endif