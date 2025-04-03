#ifndef SEAD_TREENODE_H_
#define SEAD_TREENODE_H_

#include <basis/seadTypes.h>

namespace sead
{
class TreeNode
{
public:
    TreeNode();

    void clearLinks();
    s32 countChildren() const;
    void detachAll();
    void detachSubTree();
    TreeNode* findRoot();
    const TreeNode* findRoot() const;
    void insertAfterSelf(TreeNode* node);
    void insertBeforeSelf(TreeNode* node);
    void pushBackChild(TreeNode* node);
    void pushBackSibling(TreeNode* node);
    void pushFrontChild(TreeNode* node);

protected:
    void clearChildLinksRecursively_();

    TreeNode* mParent;
    TreeNode* mChild;
    TreeNode* mNext;
    TreeNode* mPrev;
};

template <typename T>
class TTreeNode : public TreeNode
{
public:
    TTreeNode() = default;
    explicit TTreeNode(T data) : mData(data) {}

    T& value() { return mData; }
    const T& value() const { return mData; }

    TTreeNode* parent() const { return static_cast<TTreeNode*>(mParent); }
    TTreeNode* child() const { return static_cast<TTreeNode*>(mChild); }
    TTreeNode* next() const { return static_cast<TTreeNode*>(mNext); }
    TTreeNode* prev() const { return static_cast<TTreeNode*>(mPrev); }
    TTreeNode* findRoot() { return static_cast<TTreeNode*>(TreeNode::findRoot()); }
    const TTreeNode* findRoot() const { return static_cast<TTreeNode*>(TreeNode::findRoot()); }
    void insertAfterSelf(TTreeNode* node) { TreeNode::insertAfterSelf(node); }
    void insertBeforeSelf(TTreeNode* node) { TreeNode::insertBeforeSelf(node); }
    void pushBackChild(TTreeNode* node) { TreeNode::pushBackChild(node); }
    void pushBackSibling(TTreeNode* node) { TreeNode::pushBackSibling(node); }
    void pushFrontChild(TTreeNode* node) { TreeNode::pushFrontChild(node); }

    // TODO: probably iterators

protected:
    T mData;
};

template<typename T>
class IntrusiveTreeNode : public TreeNode {
    static constexpr ptrdiff_t getOffset() {
        return offsetof(T, mTreeNode);
    }
    public:
    T* valuePtr() { return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) - getOffset()); }
    const T* valuePtr() const { return reinterpret_cast<const T*>(reinterpret_cast<uintptr_t>(this) - getOffset()); }

    T& value() { return *valuePtr(); }
    const T& value() const { return *valuePtr(); }

    IntrusiveTreeNode* parent() const { return static_cast<IntrusiveTreeNode*>(mParent); }
    IntrusiveTreeNode* child() const { return static_cast<IntrusiveTreeNode*>(mChild); }
    IntrusiveTreeNode* next() const { return static_cast<IntrusiveTreeNode*>(mNext); }
    IntrusiveTreeNode* prev() const { return static_cast<IntrusiveTreeNode*>(mPrev); }
    IntrusiveTreeNode* findRoot() { return static_cast<IntrusiveTreeNode*>(TreeNode::findRoot()); }
    const IntrusiveTreeNode* findRoot() const { return static_cast<IntrusiveTreeNode*>(TreeNode::findRoot()); }
    void insertAfterSelf(IntrusiveTreeNode* node) { TreeNode::insertAfterSelf(node); }
    void insertBeforeSelf(IntrusiveTreeNode* node) { TreeNode::insertBeforeSelf(node); }
    void pushBackChild(IntrusiveTreeNode* node) { TreeNode::pushBackChild(node); }
    void pushBackSibling(IntrusiveTreeNode* node) { TreeNode::pushBackSibling(node); }
    void pushFrontChild(IntrusiveTreeNode* node) { TreeNode::pushFrontChild(node); }

    T* mPtr;
};

}  // namespace sead

#endif  // SEAD_TREENODE_H_
