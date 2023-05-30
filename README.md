# qulacs2023

## CRTP and std::variant v.s. Dynamic Dispatch(Normal Inheritance with Pure Virtual Class)
### CRTP and std::variant
```cpp
template <class T class S>
class QuantumGate {
public:
    // Specifying `template <class S>` for this function causes error "templates may not be 'virtual'"
    virtual void update_quantum_state(QuantumStateBase<S>& state) const = 0;
};

template <class S>
class X : public QuantumGate<X> {
    _target UINT;

public:
    X(UINT target) : _target(target) {}

    void update_quantum_state(QuantumStateBase<S>& state) const override {
        // ...
    }
};

template <class S>
class Y : public QuantumGate<Y, S> {};

template <class S>
class Z : public QuantumGate<Z, S> {};

template <class S>
class Circuit {
    using GateKind = std::variant<X<S>, Y<S>, Z<S>>;
    std::vector<GateKind> _gates;

public:
    void X(UINT target) {
        this->_gates.push_back(X<S>(target));
    }

    void update_quantum_state(QuantumStateBase<S>& state) const {
        for (const auto& gate : gates) {
            std::visit([&](const auto& gate) { gate.update_quantum_state(state); }, gate);
        }
    }
};
```

### Dynamic Dispatch(Normal Inheritance with Pure Virtual Class)
```cpp
class QuantumGate {
public:
    virtual void update_quantum_state(QuantumStateBase* state) const = 0;
};

class X : public QuantumGate {
public:
    void update_quantum_state(QuantumStateBase* state) const override {
        // ...
    }
};

class Y : public QuantumGate {};

class Z : public QuantumGate {};

class Circuit {
    std::vector<std::unique_ptr<QuantumGate>> gates

public:
    void update_quantum_state(QuantumStateBase* state) const {
        for (const auto& gate : gates) {
            gate->update_quantum_state(state);
        }
    }
};
```

## Pros and Cons
### CRTP and std::variant
- Pros:
    - 純粋仮想クラスによる動的ディスパッチを使わないので、実行時のオーバーヘッドが小さい
        - `std::variant` を使っているので疑わしい気もする
        - ゲートの行列演算に比べればゲートの選択によるオーバーヘッドは無視できると考えるのであれば，問題にはならない
- Cons:
    - `Circuit` の `std::variant` に含まれないゲートは，`Gate` を実装していても使えない
        - ユーザがゲートを追加しないのであれば問題にはならない
    - `std::variant` のメモリでのサイズは，候補となる型のうち一番大きなものに合わせて決まる
        - 1つでも大きい型があるときびしい
        - たぶん大きくなりうるのは密行列のゲートで，行列をポインタで持つなどすればいいかもしれない
    - `QuantumStateBase` も CRTP 化すると，その template parameter を引き回す必要がある

### Dynamic Dispatch(Normal Inheritance with Pure Virtual Class)
- Pros:
    - `Gate` を実装していれば，`Circuit` に追加できる
    - CRTP を使った実装よりはシンプルになる
- Cons:
    - 実行時のオーバーヘッドがある
    - ゲートをポインタで持つ必要がある
