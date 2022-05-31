<script setup>
import { computed, onMounted, ref } from 'vue'
import { useRouter } from 'vue-router'
import { useStore } from 'vuex'
import SpinnerIndicator from './components/SpinnerIndicator.vue'

const store = useStore()
const router = useRouter()

const authenticated = computed(() => store.getters['user/authenticated'])
const user = computed(() => store.getters['user/info'])
const userRole = computed(() => store.getters['user/role'])

const loading = ref(false)

const logout = () => {
  store.dispatch('user/logout')
  router.push('/')
}

onMounted(async () => {
  try {
    loading.value = true

    await router.isReady()

    await store.dispatch('fetchSettings')
    await store.dispatch('user/fetch')

    // loading

    router.push('/dashboard')
  } catch (error) {
    if (error.response?.status === 401) {
      console.log('asdf')
      router.push('/login')
    } else {
      throw error
    }
  } finally {
    loading.value = false
  }
})
</script>

<template>
  <header>
    <h1 v-if="!authenticated">warehouse management system</h1>

    <template v-else>
      <!-- <router-link to="/dashboard" :class="{ disabled: !authenticated }">Dashboard</router-link>
      <router-link to="/login">Login</router-link> -->

      <div class="user-info">
        <p class="fullname">
          {{ user.firstName }} {{ user.lastName }} <span class="role">{{ userRole.name }}</span>
        </p>
        <p class="login">{{ user.login }}</p>
      </div>

      <button @click="logout">Выйти</button>
    </template>
  </header>

  <div v-if="loading" class="spinner-container">
    <SpinnerIndicator />
  </div>
  <router-view v-show="!loading" />
</template>

<style lang="scss">
@import '@styles';

h1 {
  text-transform: uppercase;
}

header {
  height: 64px;
  background-color: var(--primary-color);
  display: flex;
  align-items: center;
  padding: 0 var(--horizontal-padding);
  color: white;

  @mixin active {
    color: white;
    background-color: rgba(0, 0, 0, 0.1);
  }

  button {
    display: flex;
    align-items: center;
    justify-content: center;
    height: 40px;
    padding: 8px 16px;
    text-decoration: none;
    color: darken(white, 5);
    font-weight: 600;
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

.user-info {
  margin-right: auto;

  .fullname {
    font-size: 20px;
    font-weight: 600;
  }
  .role {
    font-size: 14px;
    font-weight: 400;
    color: #eee;
    text-transform: lowercase;
  }
  .login {
    color: #ddd;
  }
}

.spinner-container {
  padding: 300px 0;
  display: flex;
  align-items: center;
  justify-content: center;
}
</style>
