```shell
ulimit -c
sudo ulimit -c unlimited
sudo sysctl -w kernel.core_pattern='core.%e.%p'
cat /proc/sys/kernel/core_pattern
```
