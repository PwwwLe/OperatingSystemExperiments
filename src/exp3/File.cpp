//
// Created by Sliver on 24-5-29.
//

#include "File.h"


File::File(const string &name, const string &permissions) : name(name), permissions(permissions), size(0),
                                                            mlp(make_unique<MultiLevelPaging>()) {
}
