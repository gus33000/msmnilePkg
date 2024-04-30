#include <PiPei.h>

#include <Library/IoLib.h>
#include <Library/PlatformPrePiLib.h>

#include "PlatformUtils.h"

VOID PlatformInitialize(VOID)
{
  //
  // Initialize GIC
  //
  // The version of Gunyah in use on Lahaina has an issue where previously
  // brought up CPUs that got turned off, will not have their GIC redistributor
  // awake on subsequent power on. In order for interrupts to work properly on
  // each CPU, we need to wake up the GIC redistributor ourselves for each CPU
  // that used to be online from the beginning of this current boot session.
  // MTP8350's XBL used 2 CPUs for multithreading, so we need to wake up
  // the redistributor for CPU 0 and CPU 1.
  //

  // Wake up redistributor for CPU 0
  MmioWrite32(
      GICR_WAKER_CURRENT_CPU,
      (MmioRead32(GICR_WAKER_CURRENT_CPU) & ~GIC_WAKER_PROCESSORSLEEP));

  // Wake up redistributor for CPU 1
  MmioWrite32(
      GICR_WAKER_CPU(1),
      (MmioRead32(GICR_WAKER_CPU(1)) & ~GIC_WAKER_PROCESSORSLEEP));
}