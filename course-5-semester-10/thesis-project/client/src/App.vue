<script setup>
import { computed, onMounted } from 'vue'
import { useRouter } from 'vue-router'
import { useStore } from 'vuex'

const store = useStore()
const router = useRouter()

const authenticated = computed(() => store.getters['user/authenticated'])

onMounted(async () => {
  try {
    await store.dispatch('user/fetch')

    // loading

    router.push('/dashboard')
  } catch (error) {
    if (error.response.status === 401) {
      router.push('/login')
    } else {
      throw error
    }
  }
})
</script>

<template>
  <header>
    <h1>warehouse management system</h1>

    <router-link to="/dashboard" :class="{ disabled: !authenticated }">Dashboard</router-link>
    <router-link to="/login">Login</router-link>
  </header>

  <router-view />
</template>

<style lang="scss">
body {
  margin: 0;
}

#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
}

code {
  font-family: source-code-pro, Menlo, Monaco, Consolas, 'Courier New', monospace;
}

@mixin appearance($value: none) {
  -webkit-appearance: $value;
  -moz-appearance: $value;
  -ms-appearance: $value;
  -o-appearance: $value;
  appearance: $value;
}

div {
  box-sizing: border-box;
}

:root {
  --primary-color: #2bae66ff;
  --primary-color-l: rgb(59, 201, 123);
  --secondary-color: #fcf6f5ff;
  --black: #101820ff;
  --grey: rgb(231, 231, 231);

  --horizontal-padding: 32px;
  --vertical-padding: 24px;
}

h1 {
  text-transform: uppercase;
}

header {
  height: 64px;
  background-color: var(--primary-color);
  display: flex;
  align-items: center;
  padding: 0 var(--horizontal-padding);

  @mixin active {
    color: white;
    background-color: rgba(0, 0, 0, 0.1);
  }

  a {
    display: flex;
    align-items: center;
    justify-content: center;
    height: 24px;
    padding: 8px 16px;
    text-decoration: none;
    color: darken(white, 5);
    font-weight: bold;
    font-size: 20px;
    transition: all 0.15s ease-in-out;

    &:hover {
      @include active;
    }
  }
  a.active {
    @include active;
  }
  a.disabled {
    opacity: 0.5;
    pointer-events: none;
  }
  a + a {
    margin-left: 12px;
  }

  h1 {
    margin-right: auto;
    font-size: 24px;
    color: white;
  }
}

input[type='submit'],
button {
  border-radius: 0;
  border: none;
  color: white;
  display: flex;
  align-items: center;
  justify-content: center;
  height: 32px;
  padding: 0 12px;
  background-color: var(--primary-color);
  font-weight: 600;
  cursor: pointer;
  transition: all 0.15s ease-in-out;

  &:hover {
    background-color: var(--primary-color-l);
  }
  &:focus {
    text-decoration: dotted underline;
    text-underline-offset: 5px;
  }
}

input:not([type='submit']) {
  @include appearance(none);

  display: block;
  border-radius: unset;
  outline: none;
  border: none;
  background-color: var(--grey);
  height: 32px;
  padding: 0 12px;
  border-bottom: 1px solid transparent;
  transition: all 0.15s;

  &:focus {
    border-bottom-color: rgb(177, 177, 177);
  }
}
</style>
