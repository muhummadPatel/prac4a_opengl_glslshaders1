/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 5.4.1
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

static const unsigned char qt_resource_data[] = {
  // /Users/muhummad/Documents/uni/CSC3020H/assignments/prac2_Opengl_intro/Games_3_GL3.2_Template/simple.frag
  0x0,0x0,0x0,0x65,
  0x23,
  0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x20,0x33,0x33,0x30,0xa,0x75,0x6e,0x69,0x66,
  0x6f,0x72,0x6d,0x20,0x76,0x65,0x63,0x34,0x20,0x66,0x63,0x6f,0x6c,0x6f,0x72,0x3b,
  0xa,0xa,0x6f,0x75,0x74,0x20,0x76,0x65,0x63,0x34,0x20,0x66,0x72,0x61,0x67,0x43,
  0x6f,0x6c,0x6f,0x72,0x3b,0xa,0x76,0x6f,0x69,0x64,0x20,0x6d,0x61,0x69,0x6e,0x28,
  0x20,0x76,0x6f,0x69,0x64,0x20,0x29,0xa,0x7b,0xa,0x20,0x20,0x20,0x20,0x66,0x72,
  0x61,0x67,0x43,0x6f,0x6c,0x6f,0x72,0x20,0x3d,0x20,0x66,0x63,0x6f,0x6c,0x6f,0x72,
  0x3b,0xa,0x7d,0xa,
    // /Users/muhummad/Documents/uni/CSC3020H/assignments/prac2_Opengl_intro/Games_3_GL3.2_Template/simple.vert
  0x0,0x0,0x0,0x67,
  0x23,
  0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x20,0x33,0x33,0x30,0xa,0x69,0x6e,0x20,0x76,
  0x65,0x63,0x34,0x20,0x76,0x65,0x72,0x74,0x65,0x78,0x3b,0xa,0xa,0x75,0x6e,0x69,
  0x66,0x6f,0x72,0x6d,0x20,0x6d,0x61,0x74,0x34,0x20,0x4d,0x56,0x50,0x3b,0xa,0xa,
  0x76,0x6f,0x69,0x64,0x20,0x6d,0x61,0x69,0x6e,0x28,0x20,0x76,0x6f,0x69,0x64,0x20,
  0x29,0xa,0x7b,0xa,0x20,0x20,0x20,0x20,0x67,0x6c,0x5f,0x50,0x6f,0x73,0x69,0x74,
  0x69,0x6f,0x6e,0x20,0x3d,0x20,0x4d,0x56,0x50,0x20,0x2a,0x20,0x76,0x65,0x72,0x74,
  0x65,0x78,0x3b,0xa,0x7d,0xa,
  
};

static const unsigned char qt_resource_name[] = {
  // simple.frag
  0x0,0xb,
  0x2,0xb0,0xd0,0x97,
  0x0,0x73,
  0x0,0x69,0x0,0x6d,0x0,0x70,0x0,0x6c,0x0,0x65,0x0,0x2e,0x0,0x66,0x0,0x72,0x0,0x61,0x0,0x67,
    // simple.vert
  0x0,0xb,
  0x2,0xb1,0xc4,0x74,
  0x0,0x73,
  0x0,0x69,0x0,0x6d,0x0,0x70,0x0,0x6c,0x0,0x65,0x0,0x2e,0x0,0x76,0x0,0x65,0x0,0x72,0x0,0x74,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,
  // :/simple.frag
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,
  // :/simple.vert
  0x0,0x0,0x0,0x1c,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x69,

};

#ifdef QT_NAMESPACE
#  define QT_RCC_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::name
#  define QT_RCC_MANGLE_NAMESPACE0(x) x
#  define QT_RCC_MANGLE_NAMESPACE1(a, b) a##_##b
#  define QT_RCC_MANGLE_NAMESPACE2(a, b) QT_RCC_MANGLE_NAMESPACE1(a,b)
#  define QT_RCC_MANGLE_NAMESPACE(name) QT_RCC_MANGLE_NAMESPACE2( \
        QT_RCC_MANGLE_NAMESPACE0(name), QT_RCC_MANGLE_NAMESPACE0(QT_NAMESPACE))
#else
#   define QT_RCC_PREPEND_NAMESPACE(name) name
#   define QT_RCC_MANGLE_NAMESPACE(name) name
#endif

#ifdef QT_NAMESPACE
namespace QT_NAMESPACE {
#endif

bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

bool qUnregisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

#ifdef QT_NAMESPACE
}
#endif

int QT_RCC_MANGLE_NAMESPACE(qInitResources_resources)();
int QT_RCC_MANGLE_NAMESPACE(qInitResources_resources)()
{
    QT_RCC_PREPEND_NAMESPACE(qRegisterResourceData)
        (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_resources)();
int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_resources)()
{
    QT_RCC_PREPEND_NAMESPACE(qUnregisterResourceData)
       (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

namespace {
   struct initializer {
       initializer() { QT_RCC_MANGLE_NAMESPACE(qInitResources_resources)(); }
       ~initializer() { QT_RCC_MANGLE_NAMESPACE(qCleanupResources_resources)(); }
   } dummy;
}
