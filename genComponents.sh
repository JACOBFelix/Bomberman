#!/usr/bin/env bash

if [ $# -eq 0 ]; then
    echo "Usage : $0 className [type:attributes]..."
    exit 1
fi

IFS='
'

capitalize() {
    first=$(tr [:lower:] [:upper:] <<< ${1:0:1})
    other=${1:1}
    echo -n "$first$other"
}

className=$(capitalize $1)

shift

cd includes/Components

cat > $className.hpp <<EOF
#pragma once

#include "BaseComponent.hpp"

namespace Component {
  class $className : public BaseComponent {
  private:
EOF

for attr in $@; do
    type=$(cut -d':' -f1 <<< $attr)
    name=$(cut -d':' -f2 <<< $attr)

    echo "    $type _$name;" >> $className.hpp
done

cat >> $className.hpp <<EOF

  public:
    $className();
    ~$className();
    $className($className const& rhs);
    $className& operator=($className const& rhs);

EOF

for attr in $@; do
    type=$(cut -d':' -f1 <<< $attr)
    name=$(cut -d':' -f2 <<< $attr)
    capitalized=$(capitalize $name)

    echo "    $type get$capitalized(void) const;" >> $className.hpp
    echo "    void set$capitalized($type const& $name);" >> $className.hpp
done

cat >> $className.hpp <<EOF
  };
}
EOF

cd ../../src/Components

cat > $className.cpp <<EOF
#include "Components/$className.hpp"

Component::$className::$className() : BaseComponent() {}

Component::$className::~$className() {}

Component::$className::$className($className const& rhs) {
EOF

for attr in $@; do
    name=$(cut -d':' -f2 <<< $attr)

    echo "  _$name = rhs._$name;" >> $className.cpp
done

cat >> $className.cpp <<EOF
}

Component::$className& Component::$className::operator=($className const& rhs) {
  if (this != &rhs) {
EOF

for attr in $@; do
    name=$(cut -d':' -f2 <<< $attr)

    echo "    _$name = rhs._$name;" >> $className.cpp
done

cat >> $className.cpp <<EOF
  }
  return *this;
}
EOF


for attr in $@; do
    type=$(cut -d':' -f1 <<< $attr)
    name=$(cut -d':' -f2 <<< $attr)
    capitalized=$(capitalize $name)

    cat >> $className.cpp <<EOF
$type Component::$className::get$capitalized(void) const {
  return _$name;
}

void Component::$className::set$capitalized($type const& $name) {
  _$name = $name;
}
EOF
done
