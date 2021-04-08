#pragma once
#include "Component.h"
#include <SDL.h>
#include <cassert>
#include "InputHandler.h"
#include "Game.h"
#include "Cursor.h"
#include "Transform.h"
#include "Sprite.h"

class MouseCtrl : public Component
{
public:
    MouseCtrl(Game* g) :
        Component(ecs::MouseCtrl), ih_(nullptr), g_(g), st(0) {};
    virtual ~MouseCtrl() {
    }

    inline void setSpeed(float speed) {
        speed = speed;
    }

    void init() override {
        tr_ = GETCMP1_(Transform);
        assert(tr_ != nullptr);
        ih_ = InputHandler::instance();
    }

    void update() override {
        game_->getWindowHeight();
        if (ih_->mouseMotionEvent()) {
            Vector2D pos = ih_->getMousePos();
            pos.set(pos.getX() - tr_->getW()/ 2, pos.getY() - tr_->getH() / 2);
            entity_->getComponent<Transform>(ecs::Transform)->setPos(pos);
        }
        
        if (st == 2) {
            Sprite* s = entity_->getComponent<Sprite>(ecs::Sprite);
            s->reset();
            st = 0;
        }
        if (st == 1) { ++st; }
        if (ih_->mouseButtonEvent()) {
            uint e = ih_->getMouseButtonState(InputHandler::LEFT);
            cout << e << endl;
            Sprite* s = entity_->getComponent<Sprite>(ecs::Sprite);
            if (e) s->avanza();
            if (!e && s->get()) {
                s->avanza(); ++st;
            }
            /*if (!e) {
                if (!s->get()) s->reset();
                else s->avanza();
            }*/
        }           
    }

private:
    InputHandler* ih_;
    Game* g_;
    Transform* tr_;
    uint st;
};