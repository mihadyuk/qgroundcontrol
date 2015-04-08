
add_library(Qt5::QGeoServiceProviderFactoryQGC MODULE IMPORTED)

_populate_Location_plugin_properties(QGeoServiceProviderFactoryQGC RELEASE "geoservices/libqtgeoservices_qgc.a")

list(APPEND Qt5Location_PLUGINS Qt5::QGeoServiceProviderFactoryQGC)
