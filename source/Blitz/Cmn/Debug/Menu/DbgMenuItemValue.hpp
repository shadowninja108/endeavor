#pragma once

#include <sead/prim/seadDelegate.h>
#include <sead/prim/seadSafeString.hpp>
#include <Lp/Utl/Conditional.hpp>
#include <Lp/Sys/Assert.hpp>

#include "DbgMenuItem.hpp"

namespace Cmn {
    struct DbgMenuItemValue : public DbgMenuItem {
        SEAD_RTTI_OVERRIDE(DbgMenuItemValue, DbgMenuItem);

        struct Editor {
            virtual ~Editor();
            virtual float calcValueStringWidth() const = 0;
            virtual void makeValueString(sead::BufferedSafeString&) const = 0;
            virtual int getEditingValuePlace() const = 0;
            virtual float calcEditingValueStringWidth() const = 0;
            virtual void makeEditingValueString(sead::BufferedSafeString&) const = 0;
            virtual void start() = 0;
            virtual void apply() = 0;
            virtual void edit() = 0;
        };

        struct IntegerEditorBase : public Editor {
            long mMin;
            long mMax;
            long mValue = 0;
            int mEditingValuePlace = 0;
            int mEditingValuePlaceNum = 0;

            IntegerEditorBase(
                long min,
                long max
            ) : mMin(min), mMax(max) {}

            virtual float calcValueStringWidth() const;
            virtual void makeValueString(sead::BufferedSafeString&) const;
            virtual int getEditingValuePlace() const;
            virtual float calcEditingValueStringWidth() const;
            virtual void makeEditingValueString(sead::BufferedSafeString&) const;
            virtual void start();
            virtual void apply();
            virtual void edit();
            virtual long getValue_() const = 0;
            virtual void setValue_(long) = 0;
        };

        template<typename T>
        struct IntegerEditor : public IntegerEditorBase {
            T* mPtr;

            IntegerEditor(
                T* ptr,
                T min,
                T max
            ) : IntegerEditorBase(static_cast<long>(min), static_cast<long>(max)), mPtr(ptr) {}

            virtual long getValue_() const;
            virtual void setValue_(long);
        };

        struct FloatingEditor : public Editor {
            float* mPtr;
            float mMin;
            float mMax;
            float mValue = 0;
            int mEditingValuePlace = 0;
            int mEditingValuePlaceNum = 0;
            
            FloatingEditor(
                float* ptr,
                float min,
                float max
            ) : mPtr(ptr), mMin(min), mMax(max) {}

            virtual ~FloatingEditor();
            virtual float calcValueStringWidth() const;
            virtual void makeValueString(sead::BufferedSafeString&) const;
            virtual int getEditingValuePlace() const;
            virtual float calcEditingValueStringWidth() const;
            virtual void makeEditingValueString(sead::BufferedSafeString&) const;
            virtual void start();
            virtual void apply();
            virtual void edit();
        };

        template<typename T>
        using BaseType = Lp::Utl::Conditional<Lp::Utl::IsFloatingPoint<T>::cResult, float, long>::Type;

        template<typename T>
        using EditorType = Lp::Utl::Conditional<Lp::Utl::IsFloatingPoint<T>::cResult, FloatingEditor, IntegerEditor<T>>::Type;

        template<typename PrimitiveT>
        DbgMenuItemValue(sead::SafeString const& label, PrimitiveT& value, BaseType<PrimitiveT> min, BaseType<PrimitiveT> max) {
            using EditorT = EditorType<PrimitiveT>;
            mLabel = label;
            mEditor = new EditorT(&value, min, max);
            LP_ASSERT_NOFMT(!sead::MemUtil::isStack(&value));
        }
        
        template<typename PrimitiveT>
        DbgMenuItemValue(sead::SafeString const& label, PrimitiveT& value, BaseType<PrimitiveT> min, BaseType<PrimitiveT> max, void (*delegate)()) {
            using EditorT = EditorType<PrimitiveT>;
            mLabel = label;
            mCB = sead::DelegateFunc(delegate);
            mEditor = new EditorT(&value, min, max);
            LP_ASSERT_NOFMT(!sead::MemUtil::isStack(&value));
        }

        template<typename PrimitiveT, typename ThisT>
        DbgMenuItemValue(sead::SafeString const& label, PrimitiveT& value, BaseType<PrimitiveT> min, BaseType<PrimitiveT> max, ThisT* instance, void (ThisT::*delegate)()) {
            using EditorT = EditorType<PrimitiveT>;
            mLabel = label;
            mCB = sead::Delegate(delegate);
            mEditor = new EditorT(&value, min, max);
            LP_ASSERT_NOFMT(!sead::MemUtil::isStack(&value));
        }

        sead::AnyDelegate mCB;
        Editor* mEditor;

        template<typename PrimitiveT>
        static auto Create(sead::SafeString const& label, PrimitiveT& value, PrimitiveT min, PrimitiveT max) {
            return new DbgMenuItemValue(label, value, min, max);
        }
    };
}