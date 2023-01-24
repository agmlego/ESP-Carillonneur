import itertools
import queue

from zeroconf import (
    IPVersion,
    ServiceBrowser,
    ServiceStateChange,
    Zeroconf,
    ZeroconfServiceTypes,
)


def find_servers(*services):
    q = queue.SimpleQueue()
    def on_service_state_change(
        zeroconf: Zeroconf, service_type: str, name: str, state_change: ServiceStateChange
    ) -> None:
        print(f"Service {name} of type {service_type} state changed: {state_change}")

        if state_change is ServiceStateChange.Added:
            info = zeroconf.get_service_info(service_type, name)
            print("Info from zeroconf.get_service_info: %r" % (info))

            if info:
                q.put(info)
            else:
                print("  No info")
            print('\n')


    zeroconf = Zeroconf(ip_version=IPVersion.All)
    browser = ServiceBrowser(zeroconf, list(services), handlers=[on_service_state_change])

    try:
        while True:
            sinfo = q.get()
            for addr in itertools.chain(sinfo._ipv4_addresses, sinfo._ipv6_addresses):
                yield addr, sinfo.port
    finally:
        zeroconf.close()
