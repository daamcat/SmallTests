TEMPLATE = subdirs


SUBDIRS += \
  ToTestStaticLibs \
  L1 \
  L2 \
  L3/el3
  
ToTestStaticLibs.depends += L1
L1.depends += L2
L1.depends += L3/el3
