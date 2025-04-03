#pragma once

#include <sead/prim/seadDelegate.h>

#include "DbgMenuItem.hpp"

namespace Cmn {

    struct DbgMenuItemFlag : public DbgMenuItem {
        SEAD_RTTI_OVERRIDE(DbgMenuItemFlag, DbgMenuItem);

        /* TODO: work out what virtual funcs belong to which... */
        struct Editor {
            virtual ~Editor();
            virtual float calcValueStringWidth() const = 0;
            virtual void makeValueString(sead::BufferedSafeString&) const = 0;
            virtual int getEditingValuePlace() const = 0;
            virtual int getEditingValuePlaceNum() const = 0;
            virtual float calcEditingValueStringWidth() const = 0;
            virtual void makeEditingValueString(sead::BufferedSafeString&) const = 0;
            virtual void start() = 0;
            virtual void apply() = 0;
            virtual void edit() = 0;
        };

        struct IntegerEditorBase : public Editor {
            ulong mValue;
            int mEditingValuePlace;
            int mEditingValuePlaceNum;

            virtual ~IntegerEditorBase();
            virtual float calcValueStringWidth() const;
            virtual void makeValueString(sead::BufferedSafeString&) const;
            virtual int getEditingValuePlace() const;
            virtual int getEditingValuePlaceNum() const;
            virtual float calcEditingValueStringWidth() const;
            virtual void makeEditingValueString(sead::BufferedSafeString&) const;
            virtual void start();
            virtual void apply();
            virtual void edit();
            virtual ulong getValue_() = 0;
            virtual void setValue_(ulong) = 0;
        };

        template<typename T>
        struct IntegerEditor : public IntegerEditorBase {
            T* mPtr;

            virtual ulong getValue_();
            virtual void setValue_(ulong);
        };

        sead::AnyDelegate mCB;
        Editor* mEditor;

        virtual ~DbgMenuItemFlag();
        virtual void makeValueString(sead::BufferedSafeString&);
        virtual float calcValueStringWidth();
        /* TODO: probably returns enums? */
        virtual int onDecide_();
        virtual int editCalc_();
        virtual void editDraw_(agl::lyr::RenderInfo const&, sead::Vector2f const&);
        
    };
}