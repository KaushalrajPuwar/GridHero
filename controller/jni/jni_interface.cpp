#include <jni.h>
#include "GameBackend.h"
#include <vector>
#include "utilities/GridUtils.h"

extern "C"
{

    // JNI function to call Warshall's Algorithm
    JNIEXPORT jobjectArray JNICALL Java_GameBackend_computeTransitiveClosure(
        JNIEnv *env, jobject, jobjectArray graph)
    {
        // Step 1: Convert Java array to C++ vector
        jsize n = env->GetArrayLength(graph);
        std::vector<std::vector<int>> cppGraph(n, std::vector<int>(n));

        for (jsize i = 0; i < n; ++i)
        {
            jintArray row = (jintArray)env->GetObjectArrayElement(graph, i);
            jint *elements = env->GetIntArrayElements(row, 0);
            for (jsize j = 0; j < n; ++j)
            {
                cppGraph[i][j] = elements[j];
            }
            env->ReleaseIntArrayElements(row, elements, 0);
        }

        // Step 2: Call Warshall's Algorithm
        std::vector<std::vector<bool>> result = GridUtils::computeTransitiveClosure(cppGraph);

        // Step 3: Convert C++ vector back to Java array
        jobjectArray javaResult = env->NewObjectArray(n, env->FindClass("[Z"), nullptr);
        for (jsize i = 0; i < n; ++i)
        {
            jbooleanArray row = env->NewBooleanArray(n);
            jboolean rowData[n];
            for (jsize j = 0; j < n; ++j)
            {
                rowData[j] = result[i][j];
            }
            env->SetBooleanArrayRegion(row, 0, n, rowData);
            env->SetObjectArrayElement(javaResult, i, row);
        }

        return javaResult;
    }
}
