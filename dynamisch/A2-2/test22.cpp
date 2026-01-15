// Testtreiber für Aufgabe 2.2: my::vector
// WS 2022 Edition
// Autor: Hartmut Schirmacher (und ich diesmal hihi)

#include <iostream>
#include <cassert>
#include "my_vector.h"
#include "payload.h"

void test_22()
{
    using my::vector;
    using std::cout;
    using std::endl;

    cout << "====== Test 22 ======" << endl;

    /**
     * 1. Reserve vs. Initialize
     * Ziel: Beweisen, dass reserve speicher holt, aber keine objekte erzeigt
     */
    {
        cout << "1. reserve & allocate ... ";

        vector<Payload> v0;
        v0.reserve(333); // speicher holen aber keine objekte bauen

        assert(v0.capacity() == 333);
        assert(v0.size() == 0);
        assert(v0.empty());

        // es hat kein Payload-ctor aufruf stattgefunden
        assert(Payload::count() == 0);
        
        cout << " done." << endl;
    }


 
    /**
     * 2. Placement new
     * Ziel: Prüfen, ob pushback in dem reserviertem speicher baut, nicht neu allokieren
     */
    {
        cout << "2. push_back() & placement new ... ";
        
        vector<Payload> v;
        v.reserve(10);

        Payload::reset_counts();

        // temp. obj. erstellen und pushen
        v.push_back(Payload(1,2,3));

        // size muss jetzt 3 sein, cap immernoch 10
        // wir haben 3 mal den ctor aufgerufen
        assert(v.size() == 1);
        assert(v.capacity() == 10);
        assert(!v.empty());

        // temp obj. erstellt --> coount++;
        // push_back kopiert es in den vector --> (copy++, count++)
        // temp obj dtor --> count--;
        // 1 obj lebt, 1 copy fand statt
        assert(Payload::count() == 1);
        assert(Payload::copy_count() == 1);

        cout << " done." << endl;
    }

    /**
     * 3. Capacity vergrößern
     * Ziel: wenn vector voll, muss vector wachsen und alle elemente verschieben
     */
    {
        cout << "3. Move und Capacity ... ";
        
        vector<Payload> v;
        v.reserve(2);
        v.push_back(Payload(1,1,1));
        v.push_back(Payload(2,2,2));

        // messungen sauber auf 0 setzen
        Payload::reset_counts();

        v.push_back(Payload(3,3,3));

        assert(v.size() == 3);
        assert(v.capacity() > 2);

        // payload 1 und payload 2 müssen in die neue capacity gemoved worden sein
        assert(Payload::move_count() >= 2);

        // nur 1 element (Payload(3,3,3) nach reset der counter hineinkopiert)
        assert(Payload::copy_count() <= 1);

        cout << " done." << endl;
    }

    

    /**
     * 4. pop_back() & destruktion
     * Ziel: pop_back muss den destructor aufrufen, obwohl kein delete stattfindet
     */
    {
        cout << "4. pop_back() & dtor ...";

        vector<Payload> v;
        v.push_back(Payload(1,1,1));

        size_t count_old = Payload::count();
        size_t capacity_old = v.capacity();

        v.pop_back();

        // obj. muss zerstört worden sein
        assert(Payload::count() == count_old - 1);

        // der speicher muss aber noch da sein
        assert(v.capacity() == capacity_old);

        cout << " done." << endl;
    }


    /**
     * 5. Rule of 5
     * Ziel: copy-ctor soll deepcopy machen, move-ctor nur pointer tauschen
     */
    {
        cout << "5. copy vs move ...";

        vector<Payload> v_src;
        v_src.push_back(Payload(10, 10, 10));

        // copy ctor test
        Payload::reset_counts();
        vector<Payload> v_copy = v_src;

        // muss deep copy sein
        assert(Payload::copy_count() == 1);
        assert(v_copy.size() == 1);
        assert(v_src.size() == 1); // original noch gleich

        // move ctor test
        Payload::reset_counts();
        vector<Payload> v_move = std::move(v_src);

        // 0, weil nur die pointer getuascht werden, payload obj werden nicht angefasst
        assert(Payload::move_count() == 0);
        assert(Payload::copy_count() == 0);
        assert(v_move.size() == 1);
        assert(v_src.size() == 0);

        // copy zuweisung test
        vector<Payload> v_copy_assign;
        v_copy_assign.push_back(Payload(20,20,20));

        Payload::reset_counts();
        v_copy_assign = v_copy; // von oben

        // 1. copyctor erstellt temp-copy von v_copy (copy_count++)
        // 2. beiden werden geswapped
        // 3. temp stirbt und nimmt das alte (20, 20, 20) mit
        assert(Payload::copy_count() == 1);
        assert(v_copy_assign.size() == 1);
        assert(v_copy_assign[0] == Payload(10,10,10));
        assert(v_copy.size() == 1);

        // move assignemtn
        Payload::reset_counts();

        v_copy_assign = std::move(v_move); // von oben

        // 1. move ctor erstellt temp aus v_move
        // 2. swap
        // 3. temp stirbt mit altem inhalt
        assert(Payload::move_count() == 0); // nur vectorpointer getauscht
        assert(Payload::copy_count() == 0);
        
        assert(v_copy_assign.size() == 1);
        assert(v_move.size() == 0); 

        cout << " done." << endl;
    }


    /**
     * 6. shrink to fit
     * Ziel: Speicher verkleinern, elemente moven
     */
    {
        cout << "6. shrink_to_fit() ...";

        vector<Payload> v;
        v.reserve(100);
        v.push_back(Payload(1,1,1));

        assert(v.capacity() == 100);
        assert(v.size() == 1);

        Payload::reset_counts();
        v.shrink_to_fit();

        assert(v.capacity() == 1);
        assert(v.size() == 1);

        assert(Payload::move_count() == 1);      

        cout << " done." << endl;
    }

    {
        // mal ausprobieren - soll vorerst nicht (!) kompilieren --> jetzt schon!
        vector<Payload> v1;
        vector<Payload> v2 = v1;
    }

} // test22()
