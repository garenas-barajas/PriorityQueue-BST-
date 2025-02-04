#pragma once

#include <iostream>
#include <sstream>

using namespace std;

template <typename T>
class prqueue
{
private:
    struct NODE
    {
        int priority;
        T value;
        NODE *parent;
        NODE *left;
        NODE *right;
        NODE *link;
    };

    NODE *root;
    size_t sz;

    // Utility pointers for begin and next.
    NODE *curr;
    NODE *temp;

    // Recursive helper function for copy constructor
    void copy_helper(NODE *&newNode, NODE *originalNode, NODE *parent)
    {
        if (originalNode == nullptr)
        {
            newNode = nullptr;
        }
        else
        {
            // Create a new node for the current value-priority pair
            newNode = new NODE;
            newNode->value = originalNode->value;
            newNode->priority = originalNode->priority;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->link = nullptr;
            newNode->parent = parent;

            // Recursively copy left subtree
            copy_helper(newNode->left, originalNode->left, newNode);

            // Recursively copy right subtree
            copy_helper(newNode->right, originalNode->right, newNode);

            // Recursively copy linked duplicates
            copy_helper(newNode->link, originalNode->link, parent);
        }
    }

    // Recursive helper function for enqueue, also handles duplicates
    void enqueue_helper(NODE *&current, T value, int priority, NODE *parent)
    {
        // Base case: if the current node is null, create a new node with the value and priority
        if (current == nullptr)
        {
            current = new NODE;
            current->value = value;
            current->priority = priority;
            current->left = nullptr;
            current->right = nullptr;
            current->parent = parent;
            current->link = nullptr;
        }
        else
        {
            // If the priority is the same, add the value to the linked list
            if (priority == current->priority)
            {
                NODE *duplicate = current;

                // Find end of linked list
                while (duplicate->link != nullptr)
                {
                    duplicate = duplicate->link;
                }

                // Create new node and add to end of linked list
                NODE *newNode = new NODE;
                newNode->value = value;
                newNode->priority = priority;
                newNode->left = nullptr;
                newNode->right = nullptr;
                newNode->parent = current;
                newNode->link = nullptr;
                duplicate->link = newNode;
            }
            else if (priority < current->priority)
            {
                enqueue_helper(current->left, value, priority, current);
            }
            else if (priority > current->priority)
            {
                enqueue_helper(current->right, value, priority, current);
            }
        }
    }

    // Recursive helper function for clear
    void clear_helper(NODE *current)
    {
        // Base case: if the current node is null, return
        if (current == nullptr)
        {
            return;
        }

        // Traverse left subtree
        clear_helper(current->left);
        // Traverse right subtree
        clear_helper(current->right);

        // Update parent pointers
        if (current->parent != nullptr)
        {
            if (current->parent->left == current)
            {
                current->parent->left = nullptr;
            }
            else if (current->parent->right == current)
            {
                current->parent->right = nullptr;
            }
        }

        // Deletes node and its duplicates
        while (current != nullptr)
        {
            NODE *toDelete = current;
            current = current->link;
            delete toDelete;
        }
    }

    // recursive helper function to traverse the tree and add the values to the string stream
    void as_string_helper(stringstream &ss, NODE *current) const
    {
        // Base case: if current node is null, return
        if (current == nullptr)
        {
            return;
        }

        // Traverse left subtree
        as_string_helper(ss, current->left);

        // Add the value and priority to the string stream and handle duplicates
        NODE *temp = current;
        while (temp != nullptr)
        {
            ss << temp->priority << " value: " << temp->value << endl;
            temp = temp->link;
        }

        // Traverse right subtree
        as_string_helper(ss, current->right);
    }

    // Recursive helper function to compare two prqueues
    bool comparison_helper(NODE *currentNode, NODE *otherNode) const
    {
        // Base case: if both nodes are null, return true
        if (currentNode == nullptr && otherNode == nullptr)
        {
            return true;
        }

        // If one node is null and the other is not, return false
        if (currentNode == nullptr || otherNode == nullptr)
        {
            return false;
        }

        // Check values and priorities
        if (currentNode->value != otherNode->value || currentNode->priority != otherNode->priority)
        {
            return false;
        }

        // Recursively check left and right subtrees
        return comparison_helper(currentNode->left, otherNode->left) && comparison_helper(currentNode->right, otherNode->right);
    }

public:
    /// Creates an empty `prqueue`.
    prqueue()
    {
        sz = 0;
        root = nullptr;
        curr = nullptr;
        temp = nullptr;
    }

    /// Copy constructor.
    prqueue(const prqueue &other)
    {
        // Recursively copy nodes from the other prqueue
        copy_helper(root, other.root, nullptr);

        // Set the size of the new prqueue
        sz = other.sz;
    }

    /// Assignment operator; `operator=`.
    prqueue &operator=(const prqueue &other)
    {
        // Check for self-assignment
        if (this != &other)
        {
            // Clear the current prqueue
            clear();

            // Recursively copy nodes from the other prqueue
            copy_helper(root, other.root, nullptr);

            // Set the size of the new prqueue
            sz = other.sz;
        }
        return *this;
    }

    /// Empties the `prqueue`, freeing all memory it controls.
    void clear()
    {
        clear_helper(root);
        root = nullptr;
        sz = 0;
    }

    /// Destructor, cleans up all memory associated with `prqueue`.
    ~prqueue()
    {
        clear();
    }

    /// Adds `value` to the `prqueue` with the given `priority`.
    void enqueue(T value, int priority)
    {
        enqueue_helper(root, value, priority, nullptr);
        sz++;
    }

    /// Returns the value with the smallest priority in the `prqueue`, but does
    /// not modify the `prqueue`.
    T peek() const
    {
        // If the tree is empty, return empty value for T
        if (root == nullptr)
        {
            return T{};
        }

        NODE *current = root;

        // Traverse the tree to find the smallest priority
        while (current->left != nullptr)
        {
            current = current->left;
        }

        return current->value;
    }

    /// Returns the value with the smallest priority in the `prqueue` and
    /// removes it from the `prqueue`.
    T dequeue()
    {
        // If the tree is empty, return empty value T
        if (root == nullptr)
        {
            return T{};
        }

        NODE *current = root;
        NODE *parent = nullptr;

        // Traverse the tree to find the smallest priority
        while (current->left != nullptr)
        {
            parent = current;
            current = current->left;
        }

        // If the node has duplicates, the head node will be returned and the tree will be updated
        if (current->link != nullptr)
        {
            NODE *duplicate = current;
            // Remove the first node in the duplicate list
            current = duplicate->link;

            // Update the BST with the next node in the linked list of duplicates
            if (duplicate->link != nullptr)
            {
                if (parent != nullptr)
                {
                    if (parent->left == duplicate)
                    {
                        parent->left = current;
                    }
                    else
                    {
                        parent->right = current;
                    }
                }
                else
                {
                    root = current;
                }
                current->parent = parent;

                // Link the right subtree of the original root to the new current node
                current->right = duplicate->right;
                if (current->right != nullptr)
                {
                    current->right->parent = current;
                }
            }

            // Store the value of the dequeued node
            T value = duplicate->value;
            delete duplicate;
            sz--;
            return value;
        }

        // If the smallest priority is the root node, adjust the root and return the value
        if (parent == nullptr)
        {
            root = current->right;
            if (root != nullptr)
            {
                root->parent = nullptr;
            }
            T value = current->value;
            delete current;
            sz--;
            return value;
        }

        // Adjust the parent's child pointer
        if (parent->left == current)
        {
            parent->left = current->right;
            if (parent->left != nullptr)
            {
                parent->left->parent = parent;
            }
        }
        else
        {
            parent->right = current->right;
            if (parent->right != nullptr)
            {
                parent->right->parent = parent;
            }
        }

        // Hold the value of the smallest priority
        T value = current->value;

        // Delete the smallest priority node before returning the value
        delete current;

        sz--;
        return value;
    }

    /// Returns the number of elements in the `prqueue`.
    size_t size() const
    {
        return sz;
    }

    /// Resets internal state for an iterative inorder traversal.
    void begin()
    {
        // Initialize curr and temp
        curr = root;
        temp = nullptr;

        // Traverse the tree to the lowest priority node
        while (curr != nullptr && curr->left != nullptr)
        {
            curr = curr->left;
        }

        // If the current node has duplicates, set temp to the next node in the linked list
        if (curr != nullptr && curr->link != nullptr)
        {
            temp = curr->link;
        }
    }

    /// Uses the internal state to return the next in-order value and priority
    /// by reference, and advances the internal state. Returns true if the
    /// reference parameters were set, and false otherwise.
    bool next(T &value, int &priority)
    {
        // Check if current node is null
        if (curr == nullptr)
        {
            return false;
        }

        value = curr->value;
        priority = curr->priority;

        // If node has duplicates, update curr to the next node in the linked list
        if (curr->link != nullptr)
        {
            curr = curr->link;
            return true;
        }
        else if (curr->link == nullptr && curr->parent != nullptr && curr->priority == curr->parent->priority)
        {
            // If no duplicates, move to the next node in the tree
            while (curr->parent && curr->priority == curr->parent->priority)
            {
                curr = curr->parent;
            }
        }

        // If the current node has a right child, move to the right child and traverse left to find the next node
        if (curr->right != nullptr)
        {
            curr = curr->right;

            while (curr->left != nullptr)
            {
                curr = curr->left;
            }

            return true;
        }
        else
        {
            // If curr node doesn't have a right child, move to parent until a node is found
            while (curr->parent != nullptr && curr == curr->parent->right)
            {
                curr = curr->parent;
            }

            curr = curr->parent;
        }

        return true;
    }

    /// Converts the `prqueue` to a string representation, with the values
    /// in-order by priority.
    string as_string() const
    {
        // Create a string stream to store the string representation of the prqueue
        stringstream ss;

        // Call the recursive helper function
        as_string_helper(ss, root);

        return ss.str();
    }

    /// Checks if the contents of `this` and `other` are equivalent.
    bool operator==(const prqueue &other) const
    {
        // Call helper
        return comparison_helper(root, other.root);
    }

    /// Returns a pointer to the root node of the BST.
    void *getRoot()
    {
        return root;
    }
};